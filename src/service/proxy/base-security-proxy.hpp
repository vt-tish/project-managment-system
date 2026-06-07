#pragma once

#include <stdexcept>

#include <src/service/auth-service.hpp>

class BaseSecurityProxy
{
protected:
    AuthService& authService;

protected:
    static std::string roleToString(User::Role role)
    {
        switch (role)
        {
            case User::UNAUTHORIZED:
                return "UNAUTHORIZED";
            case User::DEVELOPER:
                return "DEVELOPER";
            case User::MANAGER:
                return "MANAGER";
            case User::ADMIN:
                return "ADMIN";
            default:
                return "UNKNOWN";
        }
    }

    void checkRole(User::Role minRequiredRole) const
    {
        if (authService.getCurrentRole() < minRequiredRole)
            throw std::runtime_error("Access denied. " + roleToString(minRequiredRole) +
                " rights are required, given - " + roleToString(authService.getCurrentRole()));
    }

public:
    BaseSecurityProxy(AuthService& authService)
    :
        authService(authService)
    {}

    virtual ~BaseSecurityProxy() = default;

};
