#pragma once

#include <src/entities/task.hpp>
#include <src/dtos/create-task-dto.hpp>
#include <src/dtos/move-task-to-todo-dto.hpp>
#include <src/service/task-service.hpp>
#include <src/service/auth-service.hpp>
#include <src/service/proxy/base-security-proxy.hpp>

class SecurityTaskProxy : public BaseSecurityProxy, public TaskService
{
private:
    TaskService& taskService;

public:
    SecurityTaskProxy(TaskService& taskService, AuthService& authService);
public:
    void create(const CreateTaskDto& createTaskDto, std::string creatorUsername) override;
    std::vector<Task> getInbox() const override;
    std::vector<Task> getTodo() const override;
    std::vector<Task> getInProgress() const override;
    std::vector<Task> getDone() const override;
    Task getInProgressTaskById(unsigned int id) override;
    std::vector<Task> getInProgressByUserId(unsigned int userId) const override;
    std::vector<Task> getDoneByUserId(unsigned int userId) const override;
    void moveToTodo(const MoveTaskToTodoDto& moveTaskToTodoDto) override;
    Task moveToInProgress(unsigned int userId) override;
    void moveToDone(unsigned int taskId) override;
    void markAsDone(unsigned int taskId, unsigned int subtaskId) override;
    void archiveDone(std::string fileName) override;

};
