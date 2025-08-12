#include <iostream>
#include <cstdint>
#include <vector>
#include "TimeStamp.h"
using namespace std;
class Packet
{
    private:
        uint32_t packetLength;
        TimeStampType timeStamp;
        vector<uint8_t> packetData;
    public:
    
        Packet(uint32_t length, TimeStampType tsType, const vector<uint8_t>& data);

        uint32_t getLength() const;
        TimeStampType getTimeStampType() const;
        const vector<uint8_t>& getData() const;
};