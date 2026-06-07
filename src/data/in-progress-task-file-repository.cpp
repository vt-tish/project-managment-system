#include <src/data/in-progress-task-file-repository.hpp>

InProgressTaskFileRepository::InProgressTaskFileRepository()
:
    BaseFileRepository("in-progress-task.dump")
{}

void InProgressTaskFileRepository::deleteById(unsigned int id)
{
    for (unsigned int i = 0; i < entities.size(); i++)
    {
        if (entities[i].getId() == id)
        {
            entities.erase(entities.begin() + i);
            return;
        }
    }

    throw std::runtime_error("Entity with id is not found - " + std::to_string(id));
}
