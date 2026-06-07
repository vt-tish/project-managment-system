#pragma once
#include <src/ui/commands/command.hpp>

class ShowDoneCommand : public Command
{
public:
    std::string getName() const override { return "show_done"; }
    std::string getDescription() const override { return "Show tasks in Done"; }
    void execute(UIContext& context) override;
};
