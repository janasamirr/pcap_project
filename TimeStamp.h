#include <cstdint>
#pragma once

enum type {u, n};

class TimeStamp
{
    private:
    uint32_t seconds;
    uint32_t accuracy;
    
    public:
    // Constructor
    TimeStamp( uint32_t s, uint32_t us);
    uint32_t getSeconds() const;
    uint32_t getAccuracy() const;
};