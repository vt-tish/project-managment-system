#pragma once
#include "ui-state.hpp"

class LoginState : public UIState
{
public:
    LoginState() = default;
public:
    void render() override;
    std::string getPromptPrefix(UIContext& context) const override;
    void handleInput(UIContext& context, const std::string& input) override;

};
