#pragma once

#include <queue>
#include <vector>
#include <src/helpers/byte-stream/byte-stream.hpp>

template <typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
struct PriorityQueueExposer : public std::priority_queue<T, Container, Compare>
{
    static const Container& getContainer(const std::priority_queue<T, Container, Compare>& pq)
    {
        return static_cast<const PriorityQueueExposer&>(pq).c;
    }

    static Container& getContainer(std::priority_queue<T, Container, Compare>& pq)
    {
        return static_cast<PriorityQueueExposer&>(pq).c;
    }
};

template <typename T, typename Container, typename Compare>
struct ByteStreamTraits<std::priority_queue<T, Container, Compare>>
{
    static constexpr bool isSpecialized = true;

    static void read(ByteStream& stream, std::priority_queue<T, Container, Compare>& value)
    {
        value = std::priority_queue<T, Container, Compare>();

        unsigned int len = stream.read<unsigned int>();

        for (unsigned int i = 0; i < len; ++i)
            value.push(std::move(stream.read<T>()));
    }

    static void write(ByteStream& stream, const std::priority_queue<T, Container, Compare>& value)
    {
        const auto& underlyingContainer = PriorityQueueExposer<T, Container, Compare>::getContainer(value);

        unsigned int len = underlyingContainer.size();

        stream.write(len);

        for (const auto& item : underlyingContainer)
            stream.write(item);
    }
};
