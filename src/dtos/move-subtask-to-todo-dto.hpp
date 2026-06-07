#pragma once

class MoveSubtaskToTodoDto
{
public:
    const unsigned int id;
    const float hours;

public:
    MoveSubtaskToTodoDto(unsigned int id, float hours)
    :
        id(id),
        hours(hours)
    {}

};
