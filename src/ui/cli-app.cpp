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
    }

    uiContext = std::make_unique<UIContext>(std::make_unique<LoginState>(), *authService,
        *taskService, *userService);
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
