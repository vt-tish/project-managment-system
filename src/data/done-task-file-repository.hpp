#pragma once

#include <src/data/base-file-repository.hpp>
#include <src/data/done-task-repository.hpp>
#include <src/entities/task.hpp>

class DoneTaskFileRepository : public BaseFileRepository<Task>, public DoneTaskRepository
{
public:
    DoneTaskFileRepository();

};
