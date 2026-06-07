#pragma once
#include <src/ui/commands/command.hpp>

class ShowUsersCommand : public Command
{
public:
    std::string getName() const override { return "show_users"; }
    std::string getDescription() const override { return "Show all users"; }
    void execute(UIContext& context) override;
};
