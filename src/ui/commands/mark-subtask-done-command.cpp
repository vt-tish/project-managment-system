#include <iostream>
#include <src/helpers/ui/printer.hpp>
#include <src/ui/commands/mark-subtask-done-command.hpp>
#include <src/ui/ui-context.hpp>
#include <src/helpers/ui/input.hpp>

void MarkSubtaskDoneCommand::execute(UIContext& context)
{
    unsigned int taskId;
    Input::inputNumber("Enter task ID: ", taskId);

    unsigned int subtaskId;
    Input::inputNumber("Enter subtask ID: ", subtaskId);

    context.getTaskService().markAsDone(taskId, subtaskId);
    Printer::printSuccess("Subtask marked as done successfully");
}
