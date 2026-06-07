#include <memory>
#include <src/ui/commands/logout-command.hpp>
#include <src/ui/ui-context.hpp>
#include <src/ui/states/login-state.hpp>
#include <src/helpers/ui/printer.hpp>

std::string LogoutCommand::getName() const { return "logout"; }
std::string LogoutCommand::getDescription() const { return "Logs out of the current session"; }

void LogoutCommand::execute(UIContext& context)
{
    context.getAuthService().logout();
    Printer::printSuccess("Logged out successfuly");
    context.transitionTo(std::make_unique<LoginState>());
}
