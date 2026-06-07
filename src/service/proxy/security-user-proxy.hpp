#pragma once

#include <src/service/user-service.hpp>
#include <src/service/auth-service.hpp>
#include <src/service/proxy/base-security-proxy.hpp>

class SecurityUserProxy : public BaseSecurityProxy, public UserService
{
private:
    UserService& userService;

public:
    SecurityUserProxy(UserService& userService, AuthService& authService);
public:
    void create(CreateUserDto createUserDto) override;
    std::vector<UserDto> getAll() override;
    UserDto getById(unsigned int id) override;
    void changeRole(unsigned int id, User::Role newRole) override;
    void deleteById(unsigned int id) override;

};
