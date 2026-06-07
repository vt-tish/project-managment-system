#pragma once

#include <string>

#include <src/entities/task.hpp>

class TaskStringBuilder
{
private:
    const Task& task;
    std::string result;
    std::string indentStr;

public:
    TaskStringBuilder(const Task& task);

public:
    TaskStringBuilder& withIndent(std::string indent);
    TaskStringBuilder& appendId();
    TaskStringBuilder& appendTitle();
    TaskStringBuilder& appendDescription();
    TaskStringBuilder& appendPriority();
    TaskStringBuilder& appendPoints();
    TaskStringBuilder& appendStatus();
    TaskStringBuilder& appendSubtasks();
    TaskStringBuilder& appendTimestamps();

    std::string build() const;

};
