#pragma once

#include <src/entities/entity.hpp>
#include <src/entities/task-component.hpp>

class Subtask : public Entity<Subtask>, public TaskComponent
{
private:
    std::string title;
    std::string description;

public:
    Subtask() = default;
    Subtask(std::string title, std::string description);
public:
    void read(ByteStream& byteStream) override;
    void write(ByteStream& byteStream) const override;

    std::string getTitle() const;
    std::string getDescription() const;

};

