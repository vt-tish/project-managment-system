#include <iostream>
#include <src/helpers/ui/printer.hpp>
#include <src/ui/commands/create-task-command.hpp>
#include <src/ui/ui-context.hpp>
#include <src/helpers/ui/input.hpp>
#include <src/dtos/create-task-dto.hpp>

void CreateTaskCommand::execute(UIContext& context)
{
    std::string title, description;
    Input::inputString("Enter title: ", title);
    Input::inputString("Enter description: ", description);

    std::vector<CreateSubtaskDto> subtasks;
    bool addSubtask;
    Input::inputLogic("Add subtasks? (y/n): ", addSubtask);
    
    while (addSubtask)
    {
        std::string subtaskTitle, subtaskDesc;
        Input::inputString("Enter subtask title: ", subtaskTitle);
        Input::inputString("Enter subtask description: ", subtaskDesc);
        subtasks.emplace_back(subtaskTitle, subtaskDesc);
        
        Input::inputLogic("Add another subtask? (y/n): ", addSubtask);
    }

    CreateTaskDto dto(title, description, subtasks);
    context.getTaskService().create(dto, context.getAuthService().getCurrentUsername());
    Printer::printSuccess("Task created successfully");
}
