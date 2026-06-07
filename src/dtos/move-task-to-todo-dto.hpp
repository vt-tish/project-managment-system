#pragma once

#include <string>
#include <vector>

#include <src/dtos/move-subtask-to-todo-dto.hpp>

class MoveTaskToTodoDto
{
public:
    const unsigned int priority;
    const unsigned int points;
    const float hours;
    const std::string assignedUsername;
    const std::vector<MoveSubtaskToTodoDto> subtasks;

public:
    MoveTaskToTodoDto(unsigned int priority, unsigned int points, float hours,
        std::string assignedToUsername, std::vector<MoveSubtaskToTodoDto> subtasks = {})
    :
        priority(priority),
        points(points),
        hours(hours),
        assignedUsername(std::move(assignedToUsername)),
        subtasks(std::move(subtasks))
    {}

};
