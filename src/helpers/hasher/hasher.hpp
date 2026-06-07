#pragma once

#include <string>

class Hasher
{
public:
    virtual ~Hasher() = default;
    virtual unsigned long long hash(const std::string& str) const = 0;

};
