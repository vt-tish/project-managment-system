#include <src/data/todo-task-file-repository.hpp>
#include <src/helpers/byte-stream/priority-queue-serialization.hpp>

TodoTaskFileRepository::TodoTaskFileRepository()
:
    BaseFileRepository("todo-task.dump")
{}

std::vector<Task>::iterator TodoTaskFileRepository::begin()
{
    return PriorityQueueExposer<Task>::getContainer(entities).begin();
}
std::vector<Task>::iterator TodoTaskFileRepository::end()
{
    return PriorityQueueExposer<Task>::getContainer(entities).end();
}
void TodoTaskFileRepository::add(const Task& entity) { entities.push(entity); }
void TodoTaskFileRepository::onEntityUpdated(const Task& oldEntity, const Task& newEntity)
{
    if (oldEntity.getPriority() != newEntity.getPriority())
    {
        std::make_heap(begin(), end());
        hasChanged = true;
    }
}

Task TodoTaskFileRepository::getFirst() const { return entities.top(); }
Task TodoTaskFileRepository::popFirst()
{
    if (entities.empty())
        throw std::runtime_error("The todo is empty");

    Task task = entities.top();
    entities.pop();

    hasChanged = true;

    return task;
}
const std::vector<Task>& TodoTaskFileRepository::getSorted()
{
    if (!hasChanged)
        return sortedTasks;

    std::priority_queue<Task> tmp = entities;

    while (!tmp.empty())
    {
        sortedTasks.push_back(tmp.top());
        tmp.pop();
    }

    hasChanged = false;

    return sortedTasks;
}

void TodoTaskFileRepository::deleteById(unsigned int id)
{
    std::vector<Task>& tasks = PriorityQueueExposer<Task>::getContainer(entities);

    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i].getId() == id)
        {
            tasks.erase(tasks.begin() + i);
            std::make_heap(begin(), end());
            return;
        }
    }

    throw std::runtime_error("Entity with id is not found - " + std::to_string(id));
}
