#include <src/helpers/hasher/basic-hasher.hpp>

unsigned long long BasicHasher::hash(const std::string &str) const
{
    unsigned long long hash = 5381;

    for (char c : str) 
        hash = ((hash << 5) + hash) + c; 

    return hash;
}
