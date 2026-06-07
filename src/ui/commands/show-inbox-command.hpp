#pragma once
#include <src/ui/commands/command.hpp>

class ShowInboxCommand : public Command
{
public:
    std::string getName() const override { return "show_inbox"; }
    std::string getDescription() const override { return "Show tasks in Inbox"; }
    void execute(UIContext& context) override;
};
