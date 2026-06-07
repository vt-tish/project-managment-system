#pragma once
#include <src/ui/commands/command.hpp>

class CreateTaskCommand : public Command
{
public:
    std::string getName() const override { return "create_task"; }
    std::string getDescription() const override { return "Create a new task in Inbox"; }
    void execute(UIContext& context) override;
};
