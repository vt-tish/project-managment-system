#pragma once

#include <string>

class UIContext;

class Command
{
public:
    virtual ~Command() = default;

    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual void execute(UIContext& context) = 0;

};
