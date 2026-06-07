#pragma once

#include <string>

class Input
{
private:
    Input() = default;

private:
    static void checkExit(const std::string& inp);

public:
    static void inputNumber(const std::string question, unsigned int& out);
    static void inputNumber(const std::string question, float& out);
    static void inputLogic(const std::string question, bool& out);
    static void inputString(const std::string question, std::string& out);

};
