#pragma once

#include <iostream>

class Printer
{
public:
    Printer() = delete;
public:
    static void printSuccess(const std::string& message);
    static void printError(const std::string& message);

};
