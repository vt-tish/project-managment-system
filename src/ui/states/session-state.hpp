#pragma once

#include <map>
#include <memory>
#include <src/ui/states/ui-state.hpp>
#include <src/ui/commands/command.hpp>

class SessionState : public UIState
{
private:
    std::map<std::string, std::unique_ptr<Command>> commands;

public:
    SessionState();
public:
    void render() override;
    std::string getPromptPrefix(UIContext& context) const override;
    void handleInput(UIContext& context, const std::string& input) override;

};
