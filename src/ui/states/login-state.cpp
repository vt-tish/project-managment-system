#pragma  once

#include <iostream>

#include <src/ui/states/login-state.hpp>
#include "src/ui/ui-context.hpp"
#include <src/helpers/date-time.hpp>
#include <src/helpers/ui/input.hpp>
#include <src/ui/states/session-state.hpp>

void LoginState::render()
{
    std::cout << "========== Kanban Dashboard ==========" << std::endl;
}
std::string LoginState::getPromptPrefix(UIContext& context) const
{
    return "[" + DateTime::now().toSring() + "]: guest@UNAUTHORIZED > ";
}
void LoginState::handleInput(UIContext& context, const std::string& input)
{
    if (input != "login")
        return;

    std::string username;
    Input::inputString("Username: ", username);

    std::string password;
    Input::inputString("Password: ", password);

    try
    {
        context.getAuthService().login(username, password);
    } catch (const std::exception& e) {
        std::cout << "\tError: " << e.what() << std::endl;
        return;
    }

    context.transitionTo(std::make_unique<SessionState>());
}
