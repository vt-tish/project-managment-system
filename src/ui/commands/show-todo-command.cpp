#include <iostream>
#include <src/helpers/ui/printer.hpp>
#include <src/ui/commands/show-todo-command.hpp>
#include <src/ui/ui-context.hpp>
#include <src/helpers/ui/task-string-builder.hpp>

void ShowTodoCommand::execute(UIContext& context)
{
    auto todo = context.getTaskService().getTodo();
    if (todo.empty())
    {
        Printer::printError("Todo is empty");
        return;
    }

    std::cout << "\n--- Todo Tasks ---\n";
    for (const auto& task : todo)
    {
        std::string str = TaskStringBuilder(task)
            .appendId()
            .appendTitle()
            .appendAssignee(context.getUserService().getById(task.getAssignedUserId()).username)
            .appendPriority()
            .appendPoints()
            .appendTimestamps()
            .build();
        std::cout << str << "\n------------------\n";
    }
}
