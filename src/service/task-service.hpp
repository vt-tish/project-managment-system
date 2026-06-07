#pragma once
#include <string>
#include <vector>

#include <src/dtos/create-task-dto.hpp>
#include <src/dtos/move-task-to-todo-dto.hpp>
#include <src/entities/task.hpp>

class TaskService
{
public:
    virtual ~TaskService() = default;
    virtual void create(const CreateTaskDto& createTaskDto, std::string creatorUsername) = 0;
    virtual Task getInProgressTaskById(unsigned int id) = 0;
    virtual std::vector<Task> getInbox() const = 0;
    virtual Task getFirstInboxTask() const = 0;
    virtual std::vector<Task> getTodo() const = 0;
    virtual std::vector<Task> getInProgress() const = 0;
    virtual std::vector<Task> getDone() const = 0;
    virtual std::vector<Task> getInProgressByUserId(unsigned int userId) const = 0;
    virtual std::vector<Task> getDoneByUserId(unsigned int userId) const = 0;
    virtual void moveToTodo(const MoveTaskToTodoDto& moveTaskToTodoDto) = 0;
    virtual Task moveToInProgress(unsigned int userId) = 0;
    virtual void moveToDone(unsigned int taskId) = 0;
    virtual void markAsDone(unsigned int taskId, unsigned int subtaskId) = 0;
    virtual void archiveDone(std::string fileName) = 0;

};
