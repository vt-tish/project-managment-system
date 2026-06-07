#include <iostream>
#include <src/helpers/ui/printer.hpp>
#include <src/ui/commands/move-to-todo-command.hpp>
#include <src/ui/ui-context.hpp>
#include <src/helpers/ui/input.hpp>
#include <src/helpers/ui/task-string-builder.hpp>
#include <src/dtos/move-task-to-todo-dto.hpp>

void MoveToTodoCommand::execute(UIContext& context)
{
    try
    {
        Task task = context.getTaskService().getFirstInboxTask();
        std::string str = TaskStringBuilder(task)
            .appendId()
            .appendTitle()
            .appendDescription()
            .appendCreator(context.getUserService().getById(task.getCreatedByUserId()).username)
            .appendSubtasks()
            .build();

        std::cout << "\n--- Next Inbox Task ---\n";
        std::cout << str;
        std::cout << "\n-----------------------\n";

        unsigned int priority;
        Input::inputNumber("Enter priority (number): ", priority);

        unsigned int points;
        Input::inputNumber("Enter story points: ", points);

        float hours;
        Input::inputNumber("Enter estimated hours: ", hours);

        std::string assignee;
        Input::inputString("Enter assigned username: ", assignee);

        std::vector<MoveSubtaskToTodoDto> subtaskDtos;
        const auto& subtasks = task.getSubtasks();
        if (!subtasks.empty())
        {
            for (const auto& st : subtasks)
            {
                float stHours;
                Input::inputNumber("Enter hours for subtask '" + st.getDescription() + "': ", stHours);
                subtaskDtos.emplace_back(st.getId(), stHours);
            }
        }

        MoveTaskToTodoDto dto(priority, points, hours, assignee, subtaskDtos);
        context.getTaskService().moveToTodo(dto);
        Printer::printSuccess("Task moved to Todo successfully");
    }
    catch (const std::exception& e)
    {
        Printer::printError(e.what());
    }
}
