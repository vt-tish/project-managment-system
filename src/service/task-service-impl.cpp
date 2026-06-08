#include <stdexcept>
#include <fstream>
#include <src/service/task-service-impl.hpp>
#include <src/helpers/ui/task-string-builder.hpp>

TaskServiceImpl::TaskServiceImpl(InboxTaskRepository& inboxRepository, TodoTaskRepository& todoRepository,
                                 InProgressTaskRepository& inProgressRepository, DoneTaskRepository& doneRepository,
                                 UserRepository& userRepository)
:
    inboxRepository(inboxRepository),
    todoRepository(todoRepository),
    inProgressRepository(inProgressRepository),
    doneRepository(doneRepository),
    userRepository(userRepository)
{}

void TaskServiceImpl::create(const CreateTaskDto& createTaskDto, std::string creatorUsername)
{
    User creator = userRepository.getByUsername(creatorUsername);

    Task task = Task::builder(createTaskDto.title, creator.getId())
        .withDescription(createTaskDto.description)
        .build();

    for (const CreateSubtaskDto& subtaskDto : createTaskDto.subtasks)
        task.addSubtask(Subtask(subtaskDto.title, subtaskDto.description));

    inboxRepository.save(task);
}
Task TaskServiceImpl::getInProgressTaskById(unsigned int id) { return inProgressRepository.getById(id); }
std::vector<Task> TaskServiceImpl::getInbox() const { return inboxRepository.getAll(); }
Task TaskServiceImpl::getFirstInboxTask() const { return inboxRepository.getFirst(); }
std::vector<Task> TaskServiceImpl::getTodo() const { return todoRepository.getSorted(); }
std::vector<Task> TaskServiceImpl::getInProgress() const { return inProgressRepository.getAll(); }
std::vector<Task> TaskServiceImpl::getDone() const { return doneRepository.getAll(); }
std::vector<Task> TaskServiceImpl::getInProgressByUserId(unsigned int userId) const
{
    std::vector<Task> result;

    if (!userRepository.existsById(userId))
        throw std::runtime_error("User is not found");

    for (const Task& task : inProgressRepository.getAll())
    {
        if (userRepository.getById(task.getAssignedUserId()).getId() == userId)
            result.push_back(task);
    }

    return result;
}
std::vector<Task> TaskServiceImpl::getDoneByUserId(unsigned int userId) const
{
    std::vector<Task> result;

    if (!userRepository.existsById(userId))
        throw std::runtime_error("User is not found");

    for (const Task& task : doneRepository.getAll())
    {
        if (task.getAssignedUserId() == userId)
            result.push_back(task);
    }

    return result;
}

void TaskServiceImpl::moveToTodo(const MoveTaskToTodoDto& moveTaskToTodoDto)
{
    Task task = inboxRepository.getFirst();

    validatePriority(moveTaskToTodoDto.priority);
    task.setPriority(moveTaskToTodoDto.priority);

    validatePoints(moveTaskToTodoDto.points);
    task.setPoints(moveTaskToTodoDto.points);

    for (const MoveSubtaskToTodoDto& subtaskDto : moveTaskToTodoDto.subtasks)
    {
        validateHours(subtaskDto.hours);
        task.getSubtaskById(subtaskDto.id).setHours(subtaskDto.hours);
    }

    if (moveTaskToTodoDto.hours != 0)
    {
        validateHours(moveTaskToTodoDto.hours);
        task.setHours(moveTaskToTodoDto.hours);
    }

    task.setAssignedUserId(userRepository.getByUsername(moveTaskToTodoDto.assignedUsername).getId());

    inboxRepository.popFirst();
    todoRepository.save(task);
}
Task TaskServiceImpl::moveToInProgress(unsigned int userId)
{
    User user = userRepository.getById(userId);

    for (const Task& task : todoRepository.getSorted())
    {
        if (task.getAssignedUserId() == user.getId())
        {
            todoRepository.deleteById(task.getId());
            inProgressRepository.save(task);
            return task;
        }
    }

    throw std::runtime_error("There is no assigned tasks for " + user.getUsername());
}
void TaskServiceImpl::moveToDone(unsigned int taskId)
{
    Task task = inProgressRepository.getById(taskId);

    inProgressRepository.deleteById(task.getId());
    task.setDone();
    doneRepository.save(task);
}
void TaskServiceImpl::markAsDone(unsigned int taskId, unsigned int subtaskId)
{
    Task task = inProgressRepository.getById(taskId);

    Subtask& subtask = task.getSubtaskById(subtaskId);

    if (subtask.getIsDone())
        throw std::runtime_error("Subtask is already done");

    subtask.setDone();
    inProgressRepository.save(task);
}
void TaskServiceImpl::archiveDone(std::string fileName)
{
    std::ofstream fout(fileName, std::ios::app);
    if (!fout.is_open())
        throw std::runtime_error("Failed to open file for archiving: " + fileName);

    std::vector<Task> doneTasks = doneRepository.getAll();

    if (doneTasks.empty())
        throw std::runtime_error("Done task list is empty");

    for (const Task& task : doneTasks)
    {
        std::string creatorName = "Unknown";
        try { creatorName = userRepository.getById(task.getCreatedByUserId()).getUsername(); } catch (...) {}

        std::string assigneeName = "";
        try { assigneeName = userRepository.getById(task.getAssignedUserId()).getUsername(); } catch (...) {}

        std::string formatted = TaskStringBuilder(task)
            .appendId()
            .appendTitle()
            .appendDescription()
            .appendCreator(creatorName)
            .appendAssignee(assigneeName)
            .appendPriority()
            .appendPoints()
            .appendStatus()
            .appendSubtasks()
            .appendTimestamps()
            .build();

        fout << "=======================================\n";
        fout << formatted;
        fout << "=======================================\n\n";

        doneRepository.deleteById(task.getId());
    }
}

void TaskServiceImpl::validatePriority(unsigned int priority)
{
    if (priority > 100 || priority < 1)
        throw std::runtime_error("Priority out of range 1-100");
}
void TaskServiceImpl::validatePoints(unsigned int points)
{
    if (points > 100 || points < 1)
        throw std::runtime_error("Points out of range 1-100");
}
void TaskServiceImpl::validateHours(float hours)
{
    if (hours < 0)
        throw std::runtime_error("Hours should be positive");
}
