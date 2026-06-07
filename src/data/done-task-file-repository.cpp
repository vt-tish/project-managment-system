#include <src/data/done-task-file-repository.hpp>

DoneTaskFileRepository::DoneTaskFileRepository()
:
    BaseFileRepository("done-task.dump")
{}

void DoneTaskFileRepository::deleteById(unsigned int id)
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        if (it->getId() == id)
        {
            entities.erase(it);
            return;
        }
    }
    throw std::runtime_error("Entity with id is not found - " + std::to_string(id));
}
