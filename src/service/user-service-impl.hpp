#pragma once

#include <src/service/user-service.hpp>
#include <src/data/user-repository.hpp>
#include <src/helpers/hasher/hasher.hpp>
#include <src/dtos/user-dto.hpp>

class UserServiceImpl : public UserService
{
private:
    static constexpr unsigned int MIN_PASSWORD_LENGTH = 4;
    UserRepository& userRepository;
    Hasher& hasher;

public:
    UserServiceImpl(UserRepository& userRepository, Hasher& hasher);
public:
    void create(CreateUserDto createUserDto) override;
    std::vector<UserDto> getAll() override;
    UserDto getById(unsigned int id) override;
    void changeRole(unsigned int id, User::Role newRole) override;
    void deleteById(unsigned int id) override;

};
