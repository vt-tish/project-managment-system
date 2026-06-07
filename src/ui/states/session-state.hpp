#pragma once

#include <src/ui/states/ui-state.hpp>

class SessionState : public UIState
{
public:
    SessionState() = default;
public:
    void render() override;
    std::string getPromptPrefix(UIContext& context) const override;
    void handleInput(UIContext& context, const std::string& input) override;

};
