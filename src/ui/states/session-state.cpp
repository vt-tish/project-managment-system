#include <iostream>
#include <src/helpers/ui/printer.hpp>
#include <src/ui/states/session-state.hpp>
#include <src/ui/ui-context.hpp>
#include <src/helpers/date-time.hpp>
#include <src/service/proxy/base-security-proxy.hpp>

#include <src/ui/commands/archive-done-command.hpp>
#include <src/ui/commands/logout-command.hpp>
#include <src/ui/commands/create-task-command.hpp>
#include <src/ui/commands/show-inbox-command.hpp>
#include <src/ui/commands/move-to-todo-command.hpp>
#include <src/ui/commands/show-todo-command.hpp>
#include <src/ui/commands/move-to-in-progress-command.hpp>
#include <src/ui/commands/show-in-progress-command.hpp>
#include <src/ui/commands/mark-subtask-done-command.hpp>
#include <src/ui/commands/move-to-done-command.hpp>
#include <src/ui/commands/show-done-command.hpp>
#include <src/ui/commands/create-user-command.hpp>
#include <src/ui/commands/change-role-command.hpp>
#include <src/ui/commands/show-users-command.hpp>

SessionState::SessionState()
{
    commands.push_back(std::make_unique<ShowInboxCommand>());
    commands.push_back(std::make_unique<ShowTodoCommand>());
    commands.push_back(std::make_unique<ShowInProgressCommand>());
    commands.push_back(std::make_unique<ShowDoneCommand>());
    commands.push_back(std::make_unique<ShowUsersCommand>());

    commands.push_back(std::make_unique<CreateTaskCommand>());
    commands.push_back(std::make_unique<CreateUserCommand>());

    commands.push_back(std::make_unique<MoveToTodoCommand>());
    commands.push_back(std::make_unique<MoveToInProgressCommand>());
    commands.push_back(std::make_unique<MoveToDoneCommand>());

    commands.push_back(std::make_unique<MarkSubtaskDoneCommand>());
    commands.push_back(std::make_unique<ArchiveDoneCommand>());

    commands.push_back(std::make_unique<ChangeRoleCommand>());

    commands.push_back(std::make_unique<LogoutCommand>());
}

void SessionState::render()
{
    std::cout << "\n--- Session Menu ---\n";
    for (const auto& cmd : commands)
    {
        std::cout << "  " << cmd->getName() << " \t- " << cmd->getDescription() << "\n";
    }
    std::cout << "--------------------\n";
}

std::string SessionState::getPromptPrefix(UIContext& context) const
{
    return "[" + DateTime::now().toSring() + "]: " + context.getAuthService().getCurrentUsername()
        + "@" + BaseSecurityProxy::roleToString(context.getAuthService().getCurrentRole()) + " > ";
}

void SessionState::handleInput(UIContext& context, const std::string &input)
{
    if (input.empty()) return;

    for (const auto& cmd : commands)
    {
        if (cmd->getName() == input)
        {
            try
            {
                cmd->execute(context);
            }
            catch (const std::exception& e)
            {
                Printer::printError(e.what());
            }
            return;
        }
    }
    
    Printer::printError("Unknown command: " + input);
}
