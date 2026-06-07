#include <src/service/proxy/security-user-proxy.hpp>

SecurityUserProxy::SecurityUserProxy(UserService& userService, AuthService& authService)
:
    userService(userService),
    BaseSecurityProxy(authService)
{}

void SecurityUserProxy::create(CreateUserDto createUserDto)
{
    checkRole(User::Role::ADMIN);
    userService.create(createUserDto);
}

std::vector<UserDto> SecurityUserProxy::getAll()
{
    checkRole(User::Role::MANAGER);
    return userService.getAll();
}

void SecurityUserProxy::changeRole(unsigned int id, User::Role newRole)
{
    checkRole(User::Role::ADMIN);
    userService.changeRole(id, newRole);
}

void SecurityUserProxy::deleteById(unsigned int id)
{
    checkRole(User::Role::ADMIN);
    userService.deleteById(id);
}
