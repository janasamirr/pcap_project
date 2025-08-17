#include "TimeStamp.h"

TimeStamp::TimeStamp( uint32_t s, uint32_t us)
    :  seconds(s), accuracy(us)
{
}
uint32_t TimeStamp::getSeconds() const {
    return seconds;
}

uint32_t TimeStamp::getAccuracy() const {
    return accuracy;
}
