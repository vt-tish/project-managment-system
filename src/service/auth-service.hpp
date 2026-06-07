#pragma once

#include <src/data/user-repository.hpp>
#include <src/helpers/hasher/hasher.hpp>

class AuthService
{
private:
    UserRepository& userRepository;
    Hasher& hasher;

    unsigned int currentUserId = 0;
    User::Role currentRole = User::Role::UNAUTHORIZED;
    std::string currentUsername;
    std::string currentFullName;

    bool isAuthenticated = false;

public:
    AuthService(UserRepository& userRepository, Hasher& hasher);
public:
    void login(const std::string& username, const std::string& password);
    void logout();

    unsigned int getCurrentUserId() const;
    std::string getCurrentUsername() const;
    std::string getCurrentFullName() const;
    User::Role getCurrentRole() const;

};
