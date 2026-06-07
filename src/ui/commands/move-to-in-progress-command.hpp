#pragma once
#include <src/ui/commands/command.hpp>

class MoveToInProgressCommand : public Command
{
public:
    std::string getName() const override { return "pull_task"; }
    std::string getDescription() const override { return "Pull next task from Todo to InProgress"; }
    void execute(UIContext& context) override;
};
