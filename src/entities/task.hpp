#pragma once

#include <vector>

#include <src/entities/entity.hpp>
#include <src/entities/subtask.hpp>
#include <src/entities/task-component.hpp>

class Task : public Entity<Task>, public TaskComponent
{
private:
    std::string title;
    std::string description;
    unsigned int priority;
    unsigned int points;
    unsigned int assignedUserId;
    unsigned int createdByUserId;
    std::vector<Subtask> subtasks;

    class Builder
    {
    private:
        std::string title;
        std::string description;
        unsigned int priority = 0;
        unsigned int points = 0;
        unsigned int assignedUserId = 0;
        unsigned int createdByUserId = 0;

        friend class Task;

    public:
        Builder(std::string& title, unsigned int createdByUserId);
    public:
        Builder& withDescription(std::string description);
        Builder& withPriority(unsigned int priority);
        Builder& withPoints(unsigned int points);
        Builder& withAssignedUserId(unsigned int assignedUserId);

        Task build() const;
    };


private:
    Task(const Builder& builder);

public:
    Task() = default;
public:
    bool operator<(const Task& obj) const;
public:
    void read(ByteStream& byteStream) override;
    void write(ByteStream& byteStream) const override;

    bool getIsDone() const override;
    void setDone() override;
    float getHours() const override;
    void setHours(float hours) override;

    std::string getTitle() const;
    std::string getDescription() const;
    unsigned int getPriority() const;
    unsigned int getPoints() const;
    unsigned int getAssignedUserId() const;
    unsigned int getCreatedByUserId() const;
    const std::vector<Subtask>& getSubtasks() const;
    Subtask& getSubtaskById(unsigned int id);

    void setPriority(unsigned int priority);
    void setPoints(unsigned int points);
    void setAssignedUserId(unsigned int assignedUserId);
    void addSubtask(const Subtask& subtaskId);

    static Builder builder(std::string title, unsigned int createdByUserId);

};
