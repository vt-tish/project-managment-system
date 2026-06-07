#include <queue>

#include <src/data/inbox-task-file-repository.hpp>

InboxTaskFileRepository::InboxTaskFileRepository()
:
    BaseFileRepository("inbox-task.dump")
{}

std::deque<Task>::iterator InboxTaskFileRepository::begin()
{
    return QueueExposer<Task>::getContainer(entities).begin();
}
std::deque<Task>::iterator InboxTaskFileRepository::end()
{
    return QueueExposer<Task>::getContainer(entities).end();
}
void InboxTaskFileRepository::add(const Task& entity) { entities.push(entity); }

Task InboxTaskFileRepository::getFirst() const { return entities.front(); }
Task InboxTaskFileRepository::popFirst()
{
    if (entities.empty())
        throw std::runtime_error("The inbox is empty");

    Task result = entities.front();
    entities.pop();

    return result;
}
