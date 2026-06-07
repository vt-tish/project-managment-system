#include <iostream>

#include <src/helpers/date-time.hpp>

#include "data/todo-task-file-repository.hpp"

int main() {
    TodoTaskFileRepository* repo = new TodoTaskFileRepository();

    repo->save(Task::builder("TestTitle1").withPriority(3).build());
    repo->save(Task::builder("TestTitle2").withPriority(2).build());
    repo->save(Task::builder("Fraud").withPriority(2).build());
    repo->save(Task::builder("TestTitle3").withPriority(1).build());

    for (const Task& it : repo->getSorted())
        std::cout << it.getTitle() << " " << it.getPriority() << std::endl;

    delete repo;

    return 0;
}
