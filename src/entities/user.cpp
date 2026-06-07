#include <src/entities/user.hpp>

User::User(std::string username, std::string fullName, unsigned long long passwordHash, Role role)
:
    username(username),
    fullName(fullName),
    passwordHash(passwordHash),
    role(role)
{}

void User::read(ByteStream& byteStream)
{
    Entity::read(byteStream);
    byteStream.read(username);
    byteStream.read(fullName);
    byteStream.read(passwordHash);
    byteStream.read(role);
}
void User::write(ByteStream& byteStream) const
{
    Entity::write(byteStream);
    byteStream.write(username);
    byteStream.write(fullName);
    byteStream.write(passwordHash);
    byteStream.write(role);
}

std::string User::getUsername() const { return username; }
std::string User::getFullName() const { return fullName; }
User::Role User::getRole() const { return role; }
unsigned long long User::getPasswordHash() const { return passwordHash; }

void User::setRole(Role role) { this->role = role; }
