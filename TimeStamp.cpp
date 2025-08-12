#include "TimeStamp.h"

TimeStamp::TimeStamp(TimeStampType t, uint32_t s, uint32_t us)
    : type(t), seconds(s), accuracy(us)
{
}
TimeStampType TimeStamp::getType() const {
    return type;
}

uint32_t TimeStamp::getSeconds() const {
    return seconds;
}

uint32_t TimeStamp::getAccuracy() const {
    return accuracy;
}
