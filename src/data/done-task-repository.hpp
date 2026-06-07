#pragma once

#include <src/data/repository.hpp>
#include <src/entities/task.hpp>

class DoneTaskRepository : public virtual Repository<Task>
{
public:
    virtual ~DoneTaskRepository() = default;

};
