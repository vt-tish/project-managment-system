#pragma once

#include <src/data/repository.hpp>
#include <src/entities/user.hpp>

class UserRepository : public virtual Repository<User>
{
public:
    virtual ~UserRepository() = default;
    virtual User getByUsername(const std::string& username) = 0;
    virtual bool existsByUsername(const std::string& username) = 0;
    virtual void deleteById(unsigned int id) = 0;

};
