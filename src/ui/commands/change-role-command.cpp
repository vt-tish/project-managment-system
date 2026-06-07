#include <iostream>
#include <src/helpers/ui/printer.hpp>
#include <src/ui/commands/change-role-command.hpp>
#include <src/ui/ui-context.hpp>
#include <src/helpers/ui/input.hpp>

void ChangeRoleCommand::execute(UIContext& context)
{
    unsigned int userId;
    Input::inputNumber("Enter user ID: ", userId);

    unsigned int roleNum;
    Input::inputNumber("Enter new role (0 for DEVELOPER, 1 for MANAGER, 2 for ADMIN): ", roleNum);
    User::Role role = User::DEVELOPER;
    if (roleNum == 1) role = User::MANAGER;
    else if (roleNum == 2) role = User::ADMIN;

    context.getUserService().changeRole(userId, role);
    Printer::printSuccess("Role changed successfully");
}
