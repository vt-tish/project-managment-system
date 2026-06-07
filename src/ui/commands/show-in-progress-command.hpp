#pragma once
#include <src/ui/commands/command.hpp>

class ShowInProgressCommand : public Command
{
public:
    std::string getName() const override { return "show_in_progress"; }
    std::string getDescription() const override { return "Show my tasks In Progress"; }
    void execute(UIContext& context) override;
};
