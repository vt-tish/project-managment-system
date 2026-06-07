#pragma once

#include <fstream>
#include <stdexcept>
#include <utility>
#include <vector>

#include <src/data/repository.hpp>
#include <src/helpers/byte-stream/byte-stream.hpp>
#include <src/entities/entity.hpp>

template <
            typename T,
            typename Container = std::vector<T>,
            typename Iterator = typename std::vector<T>::iterator
>
class BaseFileRepository : public virtual Repository<T>
{
private:
    std::string fileName;

private:
    void save()
    {
        std::ofstream fout(fileName, std::ios::binary);

        if (!fout.is_open())
            throw std::runtime_error("Failed to open file - " + fileName);

        ByteStream stream;

        stream.write(entities);

        fout.write(stream.getBuffer().data(), stream.size());
    }
    void load()
    {
        std::ifstream fin(fileName, std::ios::binary | std::ios::ate);

        if (!fin.is_open())
            return;

        std::size_t size = fin.tellg();
        fin.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);

        if (fin.read(buffer.data(), size))
        {
            ByteStream stream(std::move(buffer));
            stream.read(entities);
        }
    }

protected:
    Container entities;

protected:
    BaseFileRepository(std::string  fileName)
    :
        fileName(std::move(fileName))
    {
        static_assert(std::is_base_of_v<Entity<T>, T>, "Type T should be descendant of Entity");
        load();
    }
protected:
    virtual Iterator begin()
    {
        if constexpr (std::is_same_v<Container, std::vector<T>>)
            return entities.begin();
        else
            throw std::runtime_error("Method is not overridden");
    }
    virtual Iterator end()
    {
        if constexpr (std::is_same_v<Container, std::vector<T>>)
            return entities.end();
        else
            throw std::runtime_error("Method is not overridden");
    }

    virtual void add(const T& entity)
    {
        if constexpr (std::is_same_v<Container, std::vector<T>>)
            entities.push_back(entity);
        else
            throw std::runtime_error("Method is not overridden");
    }
    virtual void onEntityUpdated(const T& oldEntity, const T& newEntity) {}

public:
    ~BaseFileRepository() override
    {
        try
        {
            save();
        } catch (...) {}
    }
public:
    T getById(unsigned int id) override
    {
        for (const T& entity : *this)
            if (entity.getId() == id)
                return entity;

        throw std::runtime_error("Entity with id is not found - " + std::to_string(id));
    }
    bool existsById(unsigned int id) override
    {
        try
        {
            getById(id);
            return true;
        } catch (std::exception& e) {
            return false;
        }
    }
    std::vector<T> getAll() override { return std::vector<T>(begin(), end()); }
    void save(const T& entity) override
    {
        for (T& en : *this)
        {
            if (en.getId() == entity.getId())
            {
                T oldEntity = en;

                en = entity;
                onEntityUpdated(oldEntity, entity);
                return;
            }
        }

        add(entity);
    }

};
