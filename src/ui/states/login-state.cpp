#include <iostream>

#include <src/ui/states/login-state.hpp>
#include "src/ui/ui-context.hpp"
#include <src/helpers/date-time.hpp>
#include <src/helpers/ui/input.hpp>
#include <src/ui/states/session-state.hpp>
#include <src/helpers/ui/printer.hpp>

void LoginState::render()
{
    std::cout << "\n========== Kanban Dashboard ==========" << std::endl;
    std::cout << "  " << "login" << " \t- " << "To log in" << "\n";
    std::cout << "  " << "exit" << " \t- " << "To exit the application" << "\n";
    std::cout << "======================================" << std::endl;
}
std::string LoginState::getPromptPrefix(UIContext& context) const
{
    return "[" + DateTime::now().toSring() + "]: guest@UNAUTHORIZED > ";
}
void LoginState::handleInput(UIContext& context, const std::string& input)
{
    if (input.empty())
        return;

    if (input != "login")
    {
        Printer::printError("Unknown command - " + input);
        return;
    }

    std::string username;
    Input::inputString("Username: ", username);

    std::string password;
    Input::inputString("Password: ", password);

    try
    {
        context.getAuthService().login(username, password);
    } catch (const std::exception& e) {
        Printer::printError(e.what());
        return;
    }

    Printer::printSuccess("Logged in successfully");
    context.transitionTo(std::make_unique<SessionState>());
}
