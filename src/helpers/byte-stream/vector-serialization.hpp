#pragma once

#include <vector>

#include <src/helpers/byte-stream/byte-stream.hpp>

template <typename T>
struct ByteStreamTraits<std::vector<T>>
{
    static constexpr bool isSpecialized = true;

    static void read(ByteStream& stream, std::vector<T>& value)
    {
        unsigned int len = stream.read<unsigned int>();

        value.resize(len);

        for (unsigned int i = 0; i < len; ++i)
            stream.read(value[i]);
    }


    static void write(ByteStream& stream, const std::vector<T>& value)
    {
        unsigned int len = value.size();

        stream.write(len);

        for (const T& item : value)
            stream.write(item);
    }
};
