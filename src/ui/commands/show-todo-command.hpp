#pragma once
#include <src/ui/commands/command.hpp>

class ShowTodoCommand : public Command
{
public:
    std::string getName() const override { return "show_todo"; }
    std::string getDescription() const override { return "Show tasks in Todo"; }
    void execute(UIContext& context) override;
};
