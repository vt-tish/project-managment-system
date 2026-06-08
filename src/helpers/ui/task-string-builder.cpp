#include <sstream>
#include <iomanip>

#include <src/helpers/ui/task-string-builder.hpp>

TaskStringBuilder::TaskStringBuilder(const Task& task)
:
    task(task)
{}

TaskStringBuilder& TaskStringBuilder::withIndent(std::string indent)
{
    this->indentStr = indent;
    return *this;
}

TaskStringBuilder& TaskStringBuilder::appendId()
{
    result += indentStr + "ID: " + std::to_string(task.getId()) + "\n";
    return *this;
}

TaskStringBuilder& TaskStringBuilder::appendTitle()
{
    result += indentStr + "Title: " + task.getTitle() + "\n";
    return *this;
}

TaskStringBuilder& TaskStringBuilder::appendDescription()
{
    if (!task.getDescription().empty())
        result += indentStr + "Description: " + task.getDescription() + "\n";
    return *this;
}

TaskStringBuilder& TaskStringBuilder::appendPriority()
{
    result += indentStr + "Priority: " + std::to_string(task.getPriority()) + "\n";
    return *this;
}

TaskStringBuilder& TaskStringBuilder::appendPoints()
{
    result += indentStr + "Points: " + std::to_string(task.getPoints()) + "\n";
    return *this;
}

TaskStringBuilder& TaskStringBuilder::appendCreator(const std::string& creator)
{
    result += indentStr + "Created By: " + creator + "\n";
    return *this;
}

TaskStringBuilder& TaskStringBuilder::appendAssignee(const std::string& assignee)
{
    if (!assignee.empty())
        result += indentStr + "Assigned To: " + assignee + "\n";
    else
        result += indentStr + "Assigned To: Unassigned\n";
    return *this;
}

TaskStringBuilder& TaskStringBuilder::appendStatus()
{
    result += indentStr + "Status: " + (task.getIsDone() ? "Done" : "In Progress") + "\n";
    
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << task.getHours();
    result += indentStr + "Hours: " + ss.str() + "\n";
    
    return *this;
}

TaskStringBuilder& TaskStringBuilder::appendSubtasks()
{
    const auto& subtasks = task.getSubtasks();
    if (!subtasks.empty())
    {
        result += indentStr + "Subtasks:\n";
        for (const Subtask& subtask : subtasks)
        {
            result += indentStr + "  - [" + (subtask.getIsDone() ? "x" : " ") + "] "
                      + "[ID:" + std::to_string(subtask.getId()) + "] "
                      + subtask.getTitle();
                      
            std::stringstream ss;
            ss << std::fixed << std::setprecision(1) << subtask.getHours();
            result += " (" + ss.str() + "h)\n";
            
            if (!subtask.getDescription().empty())
            {
                result += indentStr + "      " + subtask.getDescription() + "\n";
            }
        }
    }
    return *this;
}

TaskStringBuilder& TaskStringBuilder::appendTimestamps()
{
    result += indentStr + "Created At: " + task.getCreatedAt().toSring() + "\n";
    if (task.getIsDone())
    {
        result += indentStr + "Done At: " + task.getDoneAt().toSring() + "\n";
    }
    return *this;
}

std::string TaskStringBuilder::build() const
{
    return result;
}
