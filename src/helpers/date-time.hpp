#pragma once

#include <ctime>
#include <string>

#include <src/helpers/byte-stream/byte-stream.hpp>

// DD-MM-YYYY hh:mm:ss
class DateTime : public ByteStreamable
{
private:
    time_t dateTime;
    std::string dateTimeStr;

    static std::string dateTimeFormat;

public:
    DateTime();
    DateTime(const DateTime& obj);
    DateTime(const std::string dateTime);
public:
    DateTime& operator=(const DateTime& obj);
    bool operator<(const DateTime& obj) const;
    bool operator>(const DateTime& obj) const;
    bool operator>=(const DateTime& obj) const;
    bool operator<=(const DateTime& obj) const;

public:
    std::string toSring() const;
    
    void read(ByteStream& byteStream) override;
    void write(ByteStream& byteStream) const override;

    static DateTime now();

};
