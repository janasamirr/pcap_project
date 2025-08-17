#include <cstdint>
#include <vector>
#include <string>
#include "TimeStamp.h"
#pragma once

using namespace std;
class PacketRecord
{
    private:
        TimeStamp stamp;
        uint32_t capturedLength;
        uint32_t originalLength;
        char* packetData;
        int dataLength;

    public:
    
        PacketRecord(TimeStamp ts,uint32_t length ,char* data);
        TimeStamp getTimeStamp() const;
        uint32_t getLength() const;
        const char* getData() const;
};