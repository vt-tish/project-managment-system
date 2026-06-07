#pragma once

#include <vector>

#include <src/entities/user.hpp>
#include <src/dtos/create-user-dto.hpp>
#include <src/dtos/user-dto.hpp>

class UserService
{
public:
    virtual ~UserService() = default;
    virtual void create(CreateUserDto createUserDto) = 0;
    virtual std::vector<UserDto> getAll() = 0;
    virtual void changeRole(unsigned int id , User::Role newRole) = 0;
    virtual void deleteById(unsigned int id) = 0;

};
