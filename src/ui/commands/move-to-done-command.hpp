#pragma once
#include <src/ui/commands/command.hpp>

class MoveToDoneCommand : public Command
{
public:
    std::string getName() const override { return "move_done"; }
    std::string getDescription() const override { return "Move an in-progress task to Done"; }
    void execute(UIContext& context) override;
};
