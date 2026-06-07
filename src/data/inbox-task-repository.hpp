#pragma once

#include <src/data/repository.hpp>
#include <src/entities/task.hpp>

class InboxTaskRepository : public virtual Repository<Task>
{
public:
    virtual ~InboxTaskRepository() = default;
    virtual Task getFirst() const = 0;
    virtual Task popFirst() = 0;

};
