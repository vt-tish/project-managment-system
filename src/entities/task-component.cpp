#include <src/entities/task-component.hpp>

void TaskComponent::read(ByteStream& byteStream)
{
    byteStream.read(hours);
    byteStream.read(isDone);
    byteStream.read(doneAt);
}
void TaskComponent::write(ByteStream& byteStream) const
{
    byteStream.write(hours);
    byteStream.write(isDone);
    byteStream.write(doneAt);
}

float TaskComponent::getHours() const { return hours; }
bool TaskComponent::getIsDone() const { return isDone; }

void TaskComponent::setHours(float hours) { this->hours = hours; }
void TaskComponent::setDone()
{
    doneAt = DateTime::now();
    isDone = true;
}

DateTime TaskComponent::getDoneAt() const { return doneAt; }
