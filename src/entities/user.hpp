#pragma once

#include <src/entities/entity.hpp>

class User : public Entity<User>
{
public:
    enum Role : int
    {
        UNAUTHORIZED = 0,
        DEVELOPER = 1,
        MANAGER = 2,
        ADMIN = 3
    };

private:
    std::string username;
    std::string fullName;
    unsigned long long passwordHash;
    Role role;

public:
    User() = default;
    User(std::string username, std::string fullName, unsigned long long passwordHash, Role role);
public:
    void read(ByteStream& byteStream) override;
    void write(ByteStream& byteStream) const override;

    std::string getUsername() const;
    std::string getFullName() const;
    Role getRole() const;
    unsigned long long getPasswordHash() const;

    void setRole(Role role);

};
