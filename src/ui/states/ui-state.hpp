#pragma once

#include <string>

class UIContext;

class UIState
{
public:
    virtual ~UIState() = default;
    virtual void render() = 0;
    virtual std::string getPromptPrefix(UIContext& context) const = 0;
    virtual void handleInput(UIContext& context, const std::string& input) = 0;

};
