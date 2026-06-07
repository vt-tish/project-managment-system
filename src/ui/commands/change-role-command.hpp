#pragma once
#include <src/ui/commands/command.hpp>

class ChangeRoleCommand : public Command
{
public:
    std::string getName() const override { return "change_role"; }
    std::string getDescription() const override { return "Change a user's role"; }
    void execute(UIContext& context) override;
};
