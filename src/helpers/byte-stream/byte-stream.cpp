#include <cstring>
#include <stdexcept>

#include <src/helpers/byte-stream/byte-stream.hpp>

ByteStream::ByteStream(std::vector<char> buffer)
:
    buffer(std::move(buffer))
{}

const std::vector<char>& ByteStream::getBuffer() const { return buffer; }
std::size_t ByteStream::size() const { return buffer.size(); }

bool ByteStream::eof() const { return pos >= buffer.size(); }

std::size_t ByteStream::tell() const { return pos; }

void ByteStream::seekToEnd() { pos = buffer.size(); }
void ByteStream::seek(const std::size_t pos) 
{
    if (pos > buffer.size()) 
        throw std::out_of_range("Seek position out of bounds");

    this->pos = pos;
}

void ByteStream::writeRaw(const void* data, std::size_t size) {
    if (size == 0) return;

    if (pos + size > buffer.size()) 
    {
        buffer.resize(pos + size);
    }

    std::memcpy(buffer.data() + pos, data, size);
    pos += size;
}
void ByteStream::readRaw(void* dest, std::size_t size) 
{
    if (size == 0) return;

    if (buffer.size() < pos + size) 
    {
        throw std::out_of_range("Read raw size out of buffer range");
    }

    std::memcpy(dest, buffer.data() + pos, size);
    pos += size;
}
