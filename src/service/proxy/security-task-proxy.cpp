#include <stdexcept>

#include <src/service/proxy/security-task-proxy.hpp>

SecurityTaskProxy::SecurityTaskProxy(TaskService& taskService, AuthService& authService)
:
    taskService(taskService),
    BaseSecurityProxy(authService)
{}

void SecurityTaskProxy::create(const CreateTaskDto &createTaskDto, std::string creatorUsername)
{
    checkRole(User::MANAGER);
    taskService.create(createTaskDto, creatorUsername);
}

std::vector<Task> SecurityTaskProxy::getInbox() const
{
    checkRole(User::DEVELOPER);
    return taskService.getInbox();
}

std::vector<Task> SecurityTaskProxy::getTodo() const
{
    checkRole(User::DEVELOPER);
    return taskService.getTodo();
}

std::vector<Task> SecurityTaskProxy::getInProgress() const
{
    checkRole(User::DEVELOPER);
    return taskService.getInProgress();
}

std::vector<Task> SecurityTaskProxy::getDone() const
{
    checkRole(User::DEVELOPER);
    return taskService.getDone();
}

std::vector<Task> SecurityTaskProxy::getInProgressByUserId(unsigned int userId) const
{
    checkRole(User::DEVELOPER);

    if (userId != authService.getCurrentUserId() && authService.getCurrentRole() < User::MANAGER)
        throw std::runtime_error("Access denied. You can only view your own tasks");

    return taskService.getInProgressByUserId(userId);
}

std::vector<Task> SecurityTaskProxy::getDoneByUser(unsigned int userId) const
{
    checkRole(User::DEVELOPER);

    if (userId != authService.getCurrentUserId() && authService.getCurrentRole() < User::MANAGER)
        throw std::runtime_error("Access denied. You can only view your own tasks");

    return taskService.getDoneByUser(userId);
}

void SecurityTaskProxy::moveToTodo(const MoveTaskToTodoDto &moveTaskToTodoDto)
{
    checkRole(User::MANAGER);
    taskService.moveToTodo(moveTaskToTodoDto);
}

Task SecurityTaskProxy::moveToInProgress(unsigned int userId)
{
    checkRole(User::DEVELOPER);

    if (userId != authService.getCurrentUserId() && authService.getCurrentRole() < User::MANAGER)
        throw std::runtime_error("Access denied. You can only pull tasks for yourself");

    return taskService.moveToInProgress(userId);
}

void SecurityTaskProxy::moveToDone(unsigned int taskId)
{
    checkRole(User::DEVELOPER);

    Task task = taskService.getInProgressTaskById(taskId);

    if (task.getAssignedUserId() != authService.getCurrentUserId() && authService.getCurrentRole() < User::MANAGER)
        throw std::runtime_error("Access denied. You can only modify tasks assigned to you");

    taskService.moveToDone(taskId);
}

void SecurityTaskProxy::markAsDone(unsigned int taskId, unsigned int subtaskId)
{
    checkRole(User::DEVELOPER);

    Task task = taskService.getInProgressTaskById(taskId);

    if (task.getAssignedUserId() != authService.getCurrentUserId() && authService.getCurrentRole() < User::MANAGER)
        throw std::runtime_error("Access denied. You can only modify tasks assigned to you");

    taskService.markAsDone(taskId, subtaskId);
}

void SecurityTaskProxy::archiveDone(std::string fileName)
{
    checkRole(User::MANAGER);
    taskService.archiveDone(fileName);
}
