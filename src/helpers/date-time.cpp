#include <ctime>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <regex>

#include <src/helpers/date-time.hpp>

DateTime::DateTime()
:
    dateTime(0),
    dateTimeStr("00-00-0000 00:00:00")
{}
DateTime::DateTime(const DateTime& obj)
{
    *this = obj;
}
DateTime::DateTime(const std::string dateTime)
:
    dateTimeStr(dateTime)
{
    std::tm t;
    std::istringstream ss(dateTime);
    std::regex pattern("^\\d{2}-\\d{2}-\\d{4} \\d{2}:\\d{2}:\\d{2}$");

    if (!std::regex_match(dateTime, pattern))
        throw std::runtime_error("Invalid time format");

    ss >> std::get_time(&t, dateTimeFormat.c_str());

    if (ss.fail())
        throw std::runtime_error("Failed to parse time");

    this->dateTime = std::mktime(&t);

    if (this->dateTime == -1)
        throw std::runtime_error("Failed to parse time");
}


DateTime& DateTime::operator=(const DateTime& obj)
{
    dateTime = obj.dateTime;
    dateTimeStr = obj.dateTimeStr;

    return *this;
}
bool DateTime::operator<(const DateTime& obj) const
{
    return dateTime < obj.dateTime;
}
bool DateTime::operator>(const DateTime& obj) const
{
    return dateTime > obj.dateTime;
}
bool DateTime::operator>=(const DateTime& obj) const
{
    return dateTime >= obj.dateTime;
}
bool DateTime::operator<=(const DateTime& obj) const
{
    return dateTime <= obj.dateTime;
}

std::string DateTime::toSring() const { return dateTimeStr; }
    
void DateTime::read(ByteStream& byteStream)
{
    byteStream.read(dateTime);
    byteStream.read(dateTimeStr);
}
void DateTime::write(ByteStream& byteStream) const {
    byteStream.write(dateTime);
    byteStream.write(dateTimeStr);
}

DateTime DateTime::now()
{
    DateTime result;
    
    result.dateTime = std::time(nullptr);
    std::tm* t = std::localtime(&result.dateTime);
    std::ostringstream ss;

    ss << std::put_time(t, dateTimeFormat.c_str());

    result.dateTimeStr = ss.str();

    return result;
}

std::string DateTime::dateTimeFormat = "%d-%m-%Y %H:%M:%S";
