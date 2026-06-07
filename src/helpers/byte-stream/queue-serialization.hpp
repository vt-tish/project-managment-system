#pragma once

#include <queue>

#include <src/helpers/byte-stream/byte-stream.hpp>

template <typename T, typename Container = std::deque<T>>
struct QueueExposer : public std::queue<T, Container>
{
    static const Container& getContainer(const std::queue<T, Container>& q)
    {
        return static_cast<const QueueExposer&>(q).c;
    }

    static Container& getContainer(std::queue<T, Container>& q)
    {
        return static_cast<QueueExposer&>(q).c;
    }
};

template <typename T, typename Container>
struct ByteStreamTraits<std::queue<T, Container>>
{
    static constexpr bool isSpecialized = true;

    static void read(ByteStream& stream, std::queue<T, Container>& value)
    {
        while (!value.empty())
            value.pop();

        unsigned int len = stream.read<unsigned int>();

        for (unsigned int i = 0; i < len; ++i)
            value.push(std::move(stream.read<T>()));
    }


    static void write(ByteStream& stream, const std::queue<T, Container>& value)
    {
        unsigned int len = value.size();
        stream.write(len);

        const auto& underlyingContainer = QueueExposer<T, Container>::getContainer(value);

        for (const auto& item : underlyingContainer)
            stream.write(item);
    }
};
