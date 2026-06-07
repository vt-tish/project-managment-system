#pragma once

#include <string>

#include <src/entities/user.hpp>

class CreateUserDto
{
public:
    const std::string username;
    const std::string password;
    const std::string fullName;
    const User::Role role;

public:
    CreateUserDto(std::string username, std::string password, std::string fullName, User::Role role)
    :
        username(std::move(username)),
        password(std::move(password)),
        fullName(std::move(fullName)),
        role(role)
    {}

};
