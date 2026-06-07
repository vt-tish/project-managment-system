#pragma once

#include <memory>
#include <src/data/inbox-task-file-repository.hpp>
#include <src/data/todo-task-file-repository.hpp>
#include <src/data/in-progress-task-file-repository.hpp>
#include <src/data/done-task-file-repository.hpp>
#include <src/data/user-file-repository.hpp>
#include <src/helpers/hasher/basic-hasher.hpp>
#include <src/service/task-service-impl.hpp>
#include <src/service/user-service-impl.hpp>
#include <src/service/auth-service.hpp>
#include <src/service/proxy/security-task-proxy.hpp>
#include <src/service/proxy/security-user-proxy.hpp>
#include <src/ui/ui-context.hpp>

class CLIApp
{
private:
    std::unique_ptr<InboxTaskFileRepository> inboxRepo;
    std::unique_ptr<TodoTaskFileRepository> todoRepo;
    std::unique_ptr<InProgressTaskFileRepository> inProgressRepo;
    std::unique_ptr<DoneTaskFileRepository> doneRepo;
    std::unique_ptr<UserFileRepository> userRepo;

    std::unique_ptr<BasicHasher> hasher;

    std::unique_ptr<TaskServiceImpl> taskServiceImpl;
    std::unique_ptr<UserServiceImpl> userServiceImpl;
    std::unique_ptr<AuthService> authService;

    std::unique_ptr<SecurityTaskProxy> taskService;
    std::unique_ptr<SecurityUserProxy> userService;

    std::unique_ptr<UIContext> uiContext;

public:
    CLIApp();
public:
    void run();

};
