#pragma once

#include <cassert>
#include <type_traits>
#include <vector>

class ByteStream;

template <typename T>
struct ByteStreamTraits 
{
    static constexpr bool isSpecialized = false;
};

class ByteStreamable
{
public:
    virtual ~ByteStreamable() = default;
    virtual void read(ByteStream& byteStream) = 0;
    virtual void write(ByteStream& byteStream) const = 0;
};

class ByteStream
{
private:
    std::size_t pos = 0;
    std::vector<char> buffer;

    template <typename T>
    inline constexpr static bool isSimpleType = std::is_trivially_copyable_v<T> && std::is_standard_layout_v<T>;

public:
    ByteStream() = default;
    ByteStream(std::vector<char> buffer);

public:
    const std::vector<char>& getBuffer() const;
    std::size_t size() const;

    bool eof() const;

    std::size_t tell() const;

    void seekToEnd();
    void seek(const std::size_t pos);

    void writeRaw(const void* data, std::size_t size);
    void readRaw(void* dest, std::size_t size);

    template <typename T> 
    void read(T& value)
    {
        if constexpr (ByteStreamTraits<T>::isSpecialized) 
            ByteStreamTraits<T>::read(*this, value);
        else if constexpr (isSimpleType<T>)
            readRaw(&value, sizeof(T));
        else if constexpr (std::is_base_of_v<ByteStreamable, T>) 
            value.read(*this);
        else 
            static_assert(sizeof(T) == 0, "Unsupported type passed to ByteStream");
    }

    template <typename T>
    T read() 
    {
        T result;
        read(result);

        return result;
    }

    template <typename T> 
    void write(const T& value) {
        if constexpr (ByteStreamTraits<T>::isSpecialized)
            ByteStreamTraits<T>::write(*this, value);
        else if constexpr (isSimpleType<T>)
            writeRaw(&value, sizeof(T));
        else if constexpr (std::is_base_of_v<ByteStreamable, T>) 
            value.write(*this);
        else 
            static_assert(sizeof(T) == 0, "Unsupported type passed to ByteStream");
    }

};

#include <src/helpers/byte-stream/string-serialization.hpp>
#include <src/helpers/byte-stream/vector-serialization.hpp>
#include <src/helpers/byte-stream/queue-serialization.hpp>
#include <src/helpers/byte-stream/priority-queue-serialization.hpp>
