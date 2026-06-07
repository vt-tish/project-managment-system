#include <iostream>
#include <src/helpers/ui/printer.hpp>
#include <src/ui/commands/show-users-command.hpp>
#include <src/ui/ui-context.hpp>
#include <src/service/proxy/base-security-proxy.hpp>

void ShowUsersCommand::execute(UIContext& context)
{
    auto users = context.getUserService().getAll();
    if (users.empty()) {
        Printer::printError("No users found");
        return;
    }
    
    std::cout << "\n--- Users ---\n";
    for (const auto& u : users) {
        std::cout << "ID: " << u.id << "\n"
                  << "Username: " << u.username << "\n"
                  << "Full Name: " << u.fullName << "\n"
                  << "Role: " << BaseSecurityProxy::roleToString(u.role) << "\n"
                  << "------------------\n";
    }
}
