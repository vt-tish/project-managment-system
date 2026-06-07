#include <iostream>
#include <src/helpers/ui/printer.hpp>
#include <src/ui/commands/show-done-command.hpp>
#include <src/ui/ui-context.hpp>
#include <src/helpers/ui/task-string-builder.hpp>

void ShowDoneCommand::execute(UIContext& context)
{
    auto doneTasks = context.getTaskService().getDone();
    
    if (doneTasks.empty())
    {
        Printer::printError("Done list is empty");
        return;
    }

    std::cout << "\n--- Done Tasks ---\n";
    for (const auto& task : doneTasks)
    {
        std::string str = TaskStringBuilder(task)
            .appendId()
            .appendTitle()
            .appendAssignee(context.getUserService().getById(task.getAssignedUserId()).username)
            .appendStatus()
            .appendTimestamps()
            .build();
        std::cout << str << "\n------------------\n";
    }
}
