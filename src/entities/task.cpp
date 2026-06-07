#include <stdexcept>
#include <src/entities/subtask.hpp>
#include <src/entities/task.hpp>
#include <string>

Task::Task(const Builder& builder)
:
    title(builder.title),
    description(builder.description),
    priority(builder.priority),
    points(builder.points),
    assignedUserId(builder.assignedUserId),
    createdByUserId(builder.createdByUserId)
{}

bool Task::operator<(const Task& obj) const { return priority < obj.priority; }

void Task::read(ByteStream& byteStream)
{
    Entity::read(byteStream);
    TaskComponent::read(byteStream);
    byteStream.read(title);
    byteStream.read(description);
    byteStream.read(priority);
    byteStream.read(points);
    byteStream.read(assignedUserId);
    byteStream.read(subtasks);
}
void Task::write(ByteStream& byteStream) const {
    Entity::write(byteStream);
    TaskComponent::write(byteStream);
    byteStream.write(title);
    byteStream.write(description);
    byteStream.write(priority);
    byteStream.write(points);
    byteStream.write(assignedUserId);
    byteStream.write(subtasks);
}

bool Task::getIsDone() const
{
    if (subtasks.empty())
        return TaskComponent::getIsDone();

    for (const Subtask& subtask : subtasks)
        if (!subtask.getIsDone())
            return false;

    return true;
}
void Task::setDone()
{
    for (Subtask& subtask : subtasks)
        subtask.setDone();

    TaskComponent::setDone();
}
float Task::getHours() const
{
    if (subtasks.empty())
        return TaskComponent::getHours();

    float result = 0.0f;

    for (const Subtask& subtask : subtasks)
        result += subtask.getHours();

    return result;
}
void Task::setHours(float hours)
{
    if (!subtasks.empty())
        throw std::runtime_error("Subtasks is not empty");

    TaskComponent::setHours(hours);
}

std::string Task::getTitle() const { return title; }
std::string Task::getDescription() const { return description; }
unsigned int Task::getPriority() const { return priority; }
unsigned int Task::getPoints() const { return points; }
unsigned int Task::getAssignedUserId() const { return assignedUserId; }
unsigned int Task::getCreatedByUserId() const { return createdByUserId; }
const std::vector<Subtask>& Task::getSubtasks() const { return subtasks; }
Subtask& Task::getSubtaskById(unsigned int id)
{
    for (Subtask& subtask : subtasks)
        if (subtask.getId() == id)
            return subtask;

    throw std::runtime_error("Subtask with id is not found - " + std::to_string(id));
}

void Task::setPriority(unsigned int priority) { this->priority = priority; }
void Task::setPoints(unsigned int points) { this->points = points; }
void Task::setAssignedUserId(unsigned int assignedUserId) { this->assignedUserId = assignedUserId; }
void Task::addSubtask(const Subtask& subtask) { subtasks.push_back(subtask); }

Task::Builder Task::builder(std::string title, unsigned int createdByUserId)
{
    return Builder(title, createdByUserId);
}
        
Task::Builder::Builder(std::string& title, unsigned int createdByUserId)
:
    title(title),
    createdByUserId(createdByUserId)
{}

Task::Builder& Task::Builder::withDescription(std::string description) 
{ 
    this->description = description; 
    return *this;
}
Task::Builder& Task::Builder::withPriority(unsigned int priority)
{ 
    this->priority = priority; 
    return *this;
}
Task::Builder& Task::Builder::withPoints(unsigned int points)
{
    this->points = points; 
    return *this;
}
Task::Builder& Task::Builder::withAssignedUserId(unsigned int assignedUserId)
{
    this->assignedUserId = assignedUserId; 
    return *this;
}

Task Task::Builder::build() const
{
    return Task(*this);
}
