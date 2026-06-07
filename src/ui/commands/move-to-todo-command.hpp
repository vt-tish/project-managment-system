#pragma once
#include <src/ui/commands/command.hpp>

class MoveToTodoCommand : public Command
{
public:
    std::string getName() const override { return "move_todo"; }
    std::string getDescription() const override { return "Move first Inbox task to Todo"; }
    void execute(UIContext& context) override;
};
