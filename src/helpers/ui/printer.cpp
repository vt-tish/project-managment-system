#include <src/helpers/ui/printer.hpp>

void Printer::printSuccess(const std::string& message)
{
    std::cout << "\t\033[32m" + message + "\033[0m\n";
}

void Printer::printError(const std::string& message)
{
    std::cout << "\t\033[31mError: " << message << "\033[0m\n";
}
