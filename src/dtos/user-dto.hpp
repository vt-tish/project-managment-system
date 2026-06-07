#pragma once

#include <string>

#include <src/entities/user.hpp>

class UserDto
{
public:
    const unsigned int id;
    const std::string username;
    const std::string fullName;
    const User::Role role;
    const DateTime createdAt;

public:
    UserDto(unsigned int id, std::string username, std::string fullName, User::Role role,
        const DateTime& createdAt)
    :
        username(std::move(username)),
        fullName(std::move(fullName)),
        role(role),
        createdAt(createdAt)
    {}

};
