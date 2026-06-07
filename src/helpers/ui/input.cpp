#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include <src/helpers/ui/input.hpp>

void Input::checkExit(const std::string& inp)
{
    if (inp == "exit")
        throw std::runtime_error("Exit");
}

void Input::inputNumber(const std::string question, unsigned int& out)
{
    std::string inp;
    unsigned int num = 0;
    std::size_t pos = 0;

    for (;;)
    {
        std::cout << question;
        std::getline(std::cin, inp);

        checkExit(inp);

        try 
        {
            num = std::stoul(inp, &pos);

            if (pos == inp.size())
            {
                out = num;
                return;
            }

            std::cout << "Error: input is not a number\n";
        } 
        catch (std::exception& ex) 
        {
            std::cout << ex.what() << std::endl;
            continue;
        }
    }
}
void Input::inputNumber(const std::string question, float& out)
{
    std::string inp;
    float num = 0;
    std::size_t pos = 0;

    for (;;)
    {
        std::cout << question;
        std::getline(std::cin, inp);

        checkExit(inp);

        try
        {
            num = std::stof(inp, &pos);

            if (pos == inp.size())
            {
                out = num;
                return;
            }

            std::cout << "Error: input is not a floating point number\n";
        } 
        catch (std::exception& ex) 
        {
            std::cout << ex.what() << std::endl;
            continue;
        }
    }
}
void Input::inputLogic(const std::string question, bool& out)
{
    std::string inp;
    for (;;)
    {
        std::cout << question;
        std::getline(std::cin, inp);

        checkExit(inp);

        if (inp == "yes")
        {
            out = true;
            return;
        }
        if (inp == "no")
        {
            out = false;
            return;
        }

        std::cout << "Error: invalid logic option, should be yes/no\n";
    }
}
void Input::inputString(const std::string question, std::string& out)
{
    std::cout << question;
    std::getline(std::cin, out);
    checkExit(out);
}
