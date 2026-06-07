#pragma once

#include <memory>

#include <src/ui/states/ui-state.hpp>
#include <src/service/auth-service.hpp>
#include <src/service/task-service.hpp>
#include <src/service/user-service.hpp>

class UIContext
{
private:
    std::unique_ptr<UIState> currentState;
    AuthService& authService;
    TaskService& taskService;
    UserService& userService;

public:
    UIContext(std::unique_ptr<UIState> initState, AuthService& authService, 
              TaskService& taskService, UserService& userService);
public:
    void transitionTo(std::unique_ptr<UIState> newState);
    void handleInput(const std::string& input);
    std::string getPromptPrefix();

    AuthService& getAuthService();
    TaskService& getTaskService();
    UserService& getUserService();

};
