#include <src/entities/subtask.hpp>

Subtask::Subtask(std::string title, std::string description)
:
    title(title),
    description(description)
{}

void Subtask::read(ByteStream& byteStream)
{
    Entity::read(byteStream);
    TaskComponent::read(byteStream);
    byteStream.read(title);
    byteStream.read(description);
}
void Subtask::write(ByteStream& byteStream) const {
    Entity::write(byteStream);
    TaskComponent::write(byteStream);
    byteStream.write(title);
    byteStream.write(description);
}

std::string Subtask::getTitle() const { return title; }
std::string Subtask::getDescription() const { return description; }
