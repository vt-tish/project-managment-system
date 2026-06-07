#pragma once

#include <src/data/base-file-repository.hpp>
#include <src/entities/task.hpp>
#include <src/data/inbox-task-repository.hpp>

class InboxTaskFileRepository : public BaseFileRepository<Task, std::queue<Task>, std::deque<Task>::iterator>,
                                public InboxTaskRepository
{
protected:
    std::deque<Task>::iterator begin() override;
    std::deque<Task>::iterator end() override;
    void add(const Task& entity) override;

public:
    InboxTaskFileRepository();
public:
    Task getFirst() const override;
    Task popFirst() override;

};
