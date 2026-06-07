#include <iostream>

#include <src/ui/cli-app.hpp>
#include <src/helpers/ui/printer.hpp>
#include <src/ui/states/login-state.hpp>

CLIApp::CLIApp()
{
    inboxRepo = std::make_unique<InboxTaskFileRepository>();
    todoRepo = std::make_unique<TodoTaskFileRepository>();
    inProgressRepo = std::make_unique<InProgressTaskFileRepository>();
    doneRepo = std::make_unique<DoneTaskFileRepository>();
    userRepo = std::make_unique<UserFileRepository>();

    hasher = std::make_unique<BasicHasher>();

    taskServiceImpl = std::make_unique<TaskServiceImpl>(*inboxRepo, *todoRepo,
        *inProgressRepo, *doneRepo, *userRepo);
    userServiceImpl = std::make_unique<UserServiceImpl>(*userRepo, *hasher);
    
    authService = std::make_unique<AuthService>(*userRepo, *hasher);

    taskService = std::make_unique<SecurityTaskProxy>(*taskServiceImpl, *authService);
    userService = std::make_unique<SecurityUserProxy>(*userServiceImpl, *authService);

    try {
        userRepo->getByUsername("admin");
    } catch (...) {
        userServiceImpl->create(CreateUserDto("admin", "admin",
            "System Administrator", User::ADMIN));
#ifdef SEED_TEST_DATA
        seedTestData();
#endif
    }

    uiContext = std::make_unique<UIContext>(std::make_unique<LoginState>(), *authService,
        *taskService, *userService);
}

void CLIApp::seedTestData() const
{
    userServiceImpl->create(CreateUserDto("dev1", "dev1",
        "Bob Developer", User::DEVELOPER));
    userServiceImpl->create(CreateUserDto("dev2", "dev2",
        "Alice Developer", User::DEVELOPER));
    userServiceImpl->create(CreateUserDto("manager1", "manager1",
        "Charlie Manager", User::MANAGER));

    unsigned int dev1Id = userRepo->getByUsername("dev1").getId();
    unsigned int dev2Id = userRepo->getByUsername("dev2").getId();

    taskServiceImpl->create(CreateTaskDto("Setup Repo", "Initial commit",
        {CreateSubtaskDto("Init git", "run git init")}), "admin");
    Task t1 = taskServiceImpl->getFirstInboxTask();
    taskServiceImpl->moveToTodo(MoveTaskToTodoDto(10, 2, 0, "dev1",
        {MoveSubtaskToTodoDto(t1.getSubtasks()[0].getId(), 1.0)}));
    Task t1Prog = taskServiceImpl->moveToInProgress(dev1Id);
    taskServiceImpl->markAsDone(t1Prog.getId(), t1Prog.getSubtasks()[0].getId());
    taskServiceImpl->moveToDone(t1Prog.getId());

    taskServiceImpl->create(CreateTaskDto("Implement Auth", "Add login/logout",
        {CreateSubtaskDto("Login UI", "create form"),
            CreateSubtaskDto("JWT", "add token generation")}), "manager1");
    Task t2 = taskServiceImpl->getFirstInboxTask();
    taskServiceImpl->moveToTodo(MoveTaskToTodoDto(5, 5, 0, "dev2",
        {MoveSubtaskToTodoDto(t2.getSubtasks()[0].getId(), 4.0),
            MoveSubtaskToTodoDto(t2.getSubtasks()[1].getId(), 6.0)}));
    taskServiceImpl->moveToInProgress(dev2Id);

    taskServiceImpl->create(CreateTaskDto("Create Dashboard", "Main view", {}),
        "manager1");
    Task t3 = taskServiceImpl->getFirstInboxTask();
    taskServiceImpl->moveToTodo(MoveTaskToTodoDto(2, 8, 15.0, "dev1",
        {}));

    taskServiceImpl->create(CreateTaskDto("Refactor DB", "Use ORM", {}),
        "manager1");
    taskServiceImpl->create(CreateTaskDto("Update README", "Add setup instructions", {}),
        "admin");
}

void CLIApp::run()
{
    std::string input;

    while (true)
    {
        std::cout << uiContext->getPromptPrefix();
        std::getline(std::cin, input);

        if (input == "exit")
        {
            std::cout << "\tExit" << std::endl;
            break;
        }

        try
        {
            uiContext->handleInput(input);
        } catch (const std::exception& e) {
            if (std::string(e.what()) == "Exit")
            {
                std::cout << "\tExit" << std::endl;
                break;
            }

            Printer::printError(e.what());
        }
    }
}
