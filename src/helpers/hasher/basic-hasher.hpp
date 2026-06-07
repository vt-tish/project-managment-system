#pragma once

#include <string>

#include <src/helpers/hasher/hasher.hpp>

class BasicHasher : public Hasher
{
public:
    unsigned long long hash(const std::string& str) const override;

};
