#pragma once

#include <src/helpers/date-time.hpp>
#include <src/helpers/byte-stream/byte-stream.hpp>

template <typename T>
class Entity : public ByteStreamable
{
private:
    static unsigned int idCounter;
    int id;
    DateTime createdAt;

public:
    Entity() 
    : 
        id(idCounter++),
        createdAt(DateTime::now())
    {}

    virtual ~Entity() = default;
public:
    unsigned int getId() const { return id; }
    DateTime getCreatedAt() const { return createdAt; }
    
    void read(ByteStream& byteStream) override
    {
        byteStream.read(id);
        
        if (id > idCounter)
            idCounter = id + 1;

        byteStream.read(createdAt);
    }
    void write(ByteStream& byteStream) const override
    {
        byteStream.write(id);
        byteStream.write(createdAt);
    }

};

template <typename T>
unsigned int Entity<T>::idCounter = 1;
