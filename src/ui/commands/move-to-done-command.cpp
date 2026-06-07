#include <iostream>
#include <src/helpers/ui/printer.hpp>
#include <src/ui/commands/move-to-done-command.hpp>
#include <src/ui/ui-context.hpp>
#include <src/helpers/ui/input.hpp>

void MoveToDoneCommand::execute(UIContext& context)
{
    unsigned int taskId;
    Input::inputNumber("Enter task ID to move to Done: ", taskId);

    context.getTaskService().moveToDone(taskId);
    Printer::printSuccess("Task moved to Done successfully");
}
