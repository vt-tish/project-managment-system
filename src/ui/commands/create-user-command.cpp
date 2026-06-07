#include <iostream>
#include <src/helpers/ui/printer.hpp>
#include <src/ui/commands/create-user-command.hpp>
#include <src/ui/ui-context.hpp>
#include <src/helpers/ui/input.hpp>
#include <src/dtos/create-user-dto.hpp>

void CreateUserCommand::execute(UIContext& context)
{
    std::string username, password, fullName;
    Input::inputString("Enter username: ", username);
    Input::inputString("Enter password: ", password);
    Input::inputString("Enter full name: ", fullName);

    unsigned int roleNum;
    Input::inputNumber("Enter role (0 for DEVELOPER, 1 for MANAGER, 2 for ADMIN): ", roleNum);
    User::Role role = User::DEVELOPER;
    if (roleNum == 1) role = User::MANAGER;
    else if (roleNum == 2) role = User::ADMIN;

    context.getUserService().create(CreateUserDto(username, password, fullName, role));
    Printer::printSuccess("User created successfully");
}
