#include <src/ui/ui-context.hpp>

UIContext::UIContext(std::unique_ptr<UIState> initState, AuthService &authService,
                     TaskService& taskService, UserService& userService)
:
    currentState(std::move(initState)),
    authService(authService),
    taskService(taskService),
    userService(userService)
{
    currentState->render();
}

void UIContext::transitionTo(std::unique_ptr<UIState> newState)
{
    currentState = std::move(newState);
    currentState->render();
}

void UIContext::handleInput(const std::string& input)
{
    if (currentState)
        currentState->handleInput(*this, input);
}

std::string UIContext::getPromptPrefix()
{
    if (currentState)
        return currentState->getPromptPrefix(*this);
    return "";
}

AuthService& UIContext::getAuthService() { return authService; }
TaskService& UIContext::getTaskService() { return taskService; }
UserService& UIContext::getUserService() { return userService; }
