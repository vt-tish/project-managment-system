#pragma once

#include <src/ui/commands/command.hpp>

class LogoutCommand : public Command
{
public:
    std::string getName() const override;
    std::string getDescription() const override;
    void execute(UIContext& context) override;

};
