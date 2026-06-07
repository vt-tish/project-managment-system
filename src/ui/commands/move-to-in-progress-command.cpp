#include <iostream>
#include <src/helpers/ui/printer.hpp>
#include <src/ui/commands/move-to-in-progress-command.hpp>
#include <src/ui/ui-context.hpp>
#include <src/helpers/ui/task-string-builder.hpp>

void MoveToInProgressCommand::execute(UIContext& context)
{
    unsigned int userId = context.getAuthService().getCurrentUserId();
    Task task = context.getTaskService().moveToInProgress(userId);
    
    std::cout << "\n--- Pulled Task ---\n";
    std::string str = TaskStringBuilder(task)
        .appendId()
        .appendTitle()
        .appendDescription()
        .appendPriority()
        .appendPoints()
        .appendSubtasks()
        .build();
    std::cout << str << "\n-------------------\n";
}
