#include <iostream>
#include <src/helpers/ui/printer.hpp>
#include <src/ui/commands/show-in-progress-command.hpp>
#include <src/ui/ui-context.hpp>
#include <src/helpers/ui/task-string-builder.hpp>

void ShowInProgressCommand::execute(UIContext& context)
{
    unsigned int userId = context.getAuthService().getCurrentUserId();
    auto tasks = context.getTaskService().getInProgressByUserId(userId);
    
    if (tasks.empty())
    {
        Printer::printError("You have no tasks in progress");
        return;
    }

    std::cout << "\n--- In Progress Tasks ---\n";
    for (const auto& task : tasks)
    {
        std::string str = TaskStringBuilder(task)
            .appendId()
            .appendTitle()
            .appendDescription()
            .appendStatus()
            .appendPriority()
            .appendPoints()
            .appendAssignee(context.getUserService().getById(task.getAssignedUserId()).username)
            .appendSubtasks()
            .appendTimestamps()
            .build();
        std::cout << str << "\n-------------------------\n";
    }
}
