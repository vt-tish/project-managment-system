#include <stdexcept>
#include <src/service/user-service-impl.hpp>

UserServiceImpl::UserServiceImpl(UserRepository& userRepository, Hasher& hasher)
:
    userRepository(userRepository),
    hasher(hasher)
{}

void UserServiceImpl::create(CreateUserDto createUserDto)
{
    if (userRepository.existsByUsername(createUserDto.username))
        throw std::runtime_error("Username already exists");


    if (createUserDto.password.size() < MIN_PASSWORD_LENGTH)
        throw std::runtime_error("Password is too short. Minimal length - "
            + std::to_string(MIN_PASSWORD_LENGTH));

    userRepository.save(User(createUserDto.username, createUserDto.fullName,
        hasher.hash(createUserDto.password), createUserDto.role));
}

std::vector<UserDto> UserServiceImpl::getAll()
{
    std::vector<UserDto> result;

    for (const User& user : userRepository.getAll())
        result.emplace_back(user.getId(), user.getUsername(),
            user.getFullName(), user.getRole(), user.getCreatedAt());

    return result;
}

UserDto UserServiceImpl::getById(unsigned int id)
{
    User user = userRepository.getById(id);
    return UserDto(user.getId(), user.getUsername(), user.getFullName(), user.getRole(), user.getCreatedAt());
}

void UserServiceImpl::changeRole(unsigned int id, User::Role newRole)
{
    User user = userRepository.getById(id);

    user.setRole(newRole);
    userRepository.save(user);
}

void UserServiceImpl::deleteById(unsigned int id) { userRepository.deleteById(id); }
