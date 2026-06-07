#include <iostream>

#include <src/helpers/date-time.hpp>
#include <src/helpers/ui/task-string-builder.hpp>

int main() 
{
    Task task = Task::builder("Implement Login UI", 1)
        .withDescription("Create a nice console UI for login process.")
        .withPriority(1)
        .withPoints(5)
        .build();

    task.addSubtask(Subtask("Read requirements", "Understand what needs to be built"));
    
    Subtask devTask("Write code", "Create the actual implementation");
    devTask.setDone();
    devTask.setHours(2.5f);
    task.addSubtask(devTask);

    std::string formattedTask = TaskStringBuilder(task)
        .appendId()
        .appendTitle()
        .appendDescription()
        .appendPriority()
        .appendPoints()
        .appendStatus()
        .appendSubtasks()
        .appendTimestamps()
        .build();

    std::cout << "--- Task Details ---\n";
    std::cout << formattedTask;
    std::cout << "--------------------\n";

    return 0;
}
