#pragma once

#include <src/entities/task.hpp>
#include <src/data/repository.hpp>

class TodoTaskRepository : public virtual Repository<Task>
{
public:
    virtual ~TodoTaskRepository() = default;
    virtual Task getFirst() const = 0;
    virtual Task popFirst() = 0;
    virtual const std::vector<Task>& getSorted() = 0;
    virtual void deleteById(unsigned int id) = 0;

};
