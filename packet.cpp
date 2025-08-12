#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include "TimeStamp.h"
#include "packet.h"
using namespace std;

    //constructor
        Packet::Packet(uint32_t length, TimeStampType tsType, const std::vector<uint8_t>& data)
        : packetLength(length), timeStamp(tsType), packetData(data)
        {
        }

        //getters
        
        uint32_t Packet::getLength() const 
        { 
            return packetLength; 
        }
        TimeStampType Packet::getTimeStampType() const 
        {
        return timeStamp;
        }
        const vector<uint8_t>& Packet:: getData() const 
        { 
            return packetData; 
        }
