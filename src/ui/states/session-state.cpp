#include <iostream>
#include <src/ui/states/session-state.hpp>
#include <src/helpers/date-time.hpp>
#include <src/service/proxy/base-security-proxy.hpp>
#include <src/ui/ui-context.hpp>
#include <src/ui/commands/archive-done-command.hpp>
#include <src/ui/commands/logout-command.hpp>
#include <src/helpers/ui/printer.hpp>

SessionState::SessionState()
{
    auto archiveCmd = std::make_unique<ArchiveDoneCommand>();
    commands[archiveCmd->getName()] = std::move(archiveCmd);
    
    auto logoutCmd = std::make_unique<LogoutCommand>();
    commands[logoutCmd->getName()] = std::move(logoutCmd);
}

void SessionState::render()
{
    std::cout << "\n---------- Session Menu ----------\n";

    for (const auto& pair : commands)
        std::cout << "  " << pair.first << " \t- " << pair.second->getDescription() << "\n";

    std::cout << "----------------------------------\n";
}

std::string SessionState::getPromptPrefix(UIContext& context) const
{
    return "[" + DateTime::now().toSring() + "]: " + context.getAuthService().getCurrentUsername()
        + "@" + BaseSecurityProxy::roleToString(context.getAuthService().getCurrentRole()) + " > ";
}

void SessionState::handleInput(UIContext& context, const std::string &input)
{
    if (input.empty()) return;

    auto it = commands.find(input);
    if (it != commands.end())
    {
        try
        {
            it->second->execute(context);
        } catch (const std::exception& e) {
            Printer::printError(e.what());
        }
    }
    else
        Printer::printError("Unknown command - " + input);
}
