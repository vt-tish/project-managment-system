#pragma once

#include <string>

#include <src/helpers/byte-stream/byte-stream.hpp>

template <>
struct ByteStreamTraits<std::string> 
{
    static constexpr bool isSpecialized = true;

    static void read(ByteStream& stream, std::string& value)
    {
        unsigned int len = stream.read<unsigned int>();

        value.resize(len);

        if (len > 0)
            stream.readRaw(value.data(), len);
    }


    static void write(ByteStream& stream, const std::string& value)
    {
        unsigned int len = value.size();

        stream.write(len);
        
        if (len > 0)
            stream.writeRaw(value.data(), len);
    }
};
