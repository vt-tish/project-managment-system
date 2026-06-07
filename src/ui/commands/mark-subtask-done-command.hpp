#pragma once
#include <src/ui/commands/command.hpp>

class MarkSubtaskDoneCommand : public Command
{
public:
    std::string getName() const override { return "mark_subtask"; }
    std::string getDescription() const override { return "Mark a subtask as done"; }
    void execute(UIContext& context) override;
};
