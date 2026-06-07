#pragma once

#include <src/data/base-file-repository.hpp>
#include <src/entities/user.hpp>
#include <src/data/user-repository.hpp>

class UserFileRepository : public BaseFileRepository<User>, public UserRepository
{
public:
    UserFileRepository();
public:
    User getByUsername(const std::string& username) override;
    bool existsByUsername(const std::string& username) override;
    void deleteById(unsigned int id) override;

};
