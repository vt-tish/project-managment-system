#include <stdexcept>
#include <src/service/auth-service.hpp>

AuthService::AuthService(UserRepository& userRepository, Hasher& hasher)
:
    userRepository(userRepository),
    hasher(hasher)
{}

void AuthService::login(const std::string& username, const std::string& password)
{
    User user = userRepository.getByUsername(username);

    if (hasher.hash(password) != user.getPasswordHash())
        throw std::runtime_error("Invalid password");

    currentUserId = user.getId();
    currentRole = user.getRole();
    currentUsername = user.getUsername();
    currentFullName = user.getFullName();
    isAuthenticated = true;
}

void AuthService::logout()
{
    isAuthenticated = false;
    currentUserId = 0;
    currentRole = User::Role::UNAUTHORIZED;
    currentUsername = "";
    currentFullName = "";
}

unsigned int AuthService::getCurrentUserId() const { return currentUserId; }

std::string AuthService::getCurrentUsername() const { return currentUsername; }

std::string AuthService::getCurrentFullName() const { return currentFullName; }

User::Role AuthService::getCurrentRole() const { return currentRole; }
