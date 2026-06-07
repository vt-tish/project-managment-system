#pragma once

#include <string>
#include <vector>
#include <src/dtos/create-subtask-dto.hpp>

class CreateTaskDto
{
public:
    const std::string title;
    const std::string description;
    const std::vector<CreateSubtaskDto> subtasks;

public:
    CreateTaskDto(std::string title, std::string description, std::vector<CreateSubtaskDto> subtasks)
    :
        title(std::move(title)),
        description(std::move(description)),
        subtasks(std::move(subtasks))
    {}

};
