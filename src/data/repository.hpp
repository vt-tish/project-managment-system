#pragma once

#include <vector>

template <typename T>
class Repository
{
public:
    virtual ~Repository() = default;
    virtual T getById(unsigned int id) = 0;
    virtual bool existsById(unsigned int id) = 0;
    virtual std::vector<T> getAll() = 0;
    virtual void save(const T& entity) = 0;

};
