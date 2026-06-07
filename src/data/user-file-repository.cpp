#include <src/data/user-file-repository.hpp>

UserFileRepository::UserFileRepository()
:
    BaseFileRepository("user.dumb")
{}

User UserFileRepository::getByUsername(const std::string& username)
{
    for (const User& user : entities)
        if (user.getUsername() == username)
            return user;

    throw std::runtime_error("User with username is not found - " + username);
}
bool UserFileRepository::existsByUsername(const std::string& username)
{
    try
    {
        getByUsername(username);
        return true;
    } catch (std::exception& e) {
        return false;
    }
}
void UserFileRepository::deleteById(unsigned int id)
{
    for (int i = 0; i < entities.size(); ++i)
    {
        if (entities[i].getId() == id)
        {
            entities.erase(entities.begin() + i);
            return;
        }
    }

    throw std::runtime_error("Entity with id is not found - " + std::to_string(id));
}
