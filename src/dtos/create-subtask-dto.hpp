#pragma once

#include <string>

class CreateSubtaskDto
{
public:
    const std::string title;
    const std::string description;

public:
    CreateSubtaskDto(std::string title, std::string description)
    :
        title(std::move(title)),
        description(std::move(description))
    {}

};
