#include <src/ui/ui-context.hpp>

UIContext::UIContext(std::unique_ptr<UIState> initState, AuthService &authService)
:
    currentState(std::move(initState)),
    authService(authService)
{
    currentState->render();
}

void UIContext::transitionTo(std::unique_ptr<UIState> newState)
{
    currentState = std::move(newState);
    currentState->render();
}

AuthService& UIContext::getAuthService() { return authService; }
