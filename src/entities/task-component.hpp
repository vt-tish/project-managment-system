#pragma once

#include <src/helpers/byte-stream/byte-stream.hpp>
#include <src/helpers/date-time.hpp>

class TaskComponent : public ByteStreamable
{
protected:
    float hours = 0.0f;
    bool isDone = false;
    DateTime doneAt;

public:
    virtual ~TaskComponent() = default;
public:
    void read(ByteStream& byteStream) override;
    void write(ByteStream& byteStream) const override;

    virtual float getHours() const;
    virtual bool getIsDone() const;

    virtual void setHours(float hours);
    virtual void setDone();

    DateTime getDoneAt() const;

};
