#pragma once

#include <src/data/base-file-repository.hpp>
#include <src/entities/task.hpp>
#include <src/data/todo-task-repository.hpp>

class TodoTaskFileRepository : public BaseFileRepository<Task, std::priority_queue<Task>>,
                               public TodoTaskRepository
{
private:
    std::vector<Task> sortedTasks;
    bool hasChanged = true;

protected:
    std::vector<Task>::iterator begin() override;
    std::vector<Task>::iterator end() override;
    void add(const Task& entity) override;
    void onEntityUpdated(const Task& oldEntity, const Task& newEntity) override;

public:
    TodoTaskFileRepository();
public:
    Task getFirst() const override;
    Task popFirst() override;
    const std::vector<Task>& getSorted() override;
    void deleteById(unsigned int id) override;

};
