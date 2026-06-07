#pragma once
#include <src/ui/commands/command.hpp>

class CreateUserCommand : public Command
{
public:
    std::string getName() const override { return "create_user"; }
    std::string getDescription() const override { return "Create a new user"; }
    void execute(UIContext& context) override;
};
