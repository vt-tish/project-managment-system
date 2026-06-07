#pragma once

#include <src/data/repository.hpp>
#include <src/entities/task.hpp>

class InProgressTaskRepository : public virtual Repository<Task>
{
public:
    virtual ~InProgressTaskRepository() = default;
    virtual void deleteById(unsigned int id) = 0;

};
