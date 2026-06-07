#pragma once

#include <memory>

#include <src/ui/states/ui-state.hpp>
#include <src/service/auth-service.hpp>

class UIContext
{
private:
    std::unique_ptr<UIState> currentState;
    AuthService& authService;

public:
    UIContext(std::unique_ptr<UIState> initState, AuthService& authService);
public:
    void transitionTo(std::unique_ptr<UIState> newState);
    AuthService& getAuthService();

};
