#include <iostream>
#include <src/helpers/ui/printer.hpp>
#include <src/ui/commands/show-inbox-command.hpp>
#include <src/ui/ui-context.hpp>
#include <src/helpers/ui/task-string-builder.hpp>

void ShowInboxCommand::execute(UIContext& context)
{
    auto inbox = context.getTaskService().getInbox();
    if (inbox.empty())
    {
        Printer::printError("Inbox is empty");
        return;
    }

    std::cout << "\n--- Inbox Tasks ---\n";
    for (const auto& task : inbox)
    {
        std::string str = TaskStringBuilder(task)
            .appendId()
            .appendTitle()
            .appendDescription()
            .appendCreator(context.getUserService().getById(task.getCreatedByUserId()).username)
            .appendTimestamps()
            .build();
        std::cout << str << "\n-------------------\n";
    }
}
