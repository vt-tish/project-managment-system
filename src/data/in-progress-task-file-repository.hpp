#pragma once

#include <src/entities/task.hpp>
#include <src/data/in-progress-task-repository.hpp>
#include <src/data/base-file-repository.hpp>

class InProgressTaskFileRepository : public BaseFileRepository<Task>, public InProgressTaskRepository
{
public:
    InProgressTaskFileRepository();
public:
    void deleteById(unsigned int id) override;

};
