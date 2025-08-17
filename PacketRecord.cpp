#include "PacketRecord.h"

    //constructor
        PacketRecord::PacketRecord(TimeStamp ts,uint32_t length,char* data)
        : stamp(ts),dataLength(length), packetData(data)
        {
        }

        //getters  
        uint32_t PacketRecord::getLength() const 
        { 
            return dataLength; 
        }
        const char* PacketRecord:: getData() const 
        { 
            return packetData; 
        }
        TimeStamp PacketRecord:: getTimeStamp() const
        {
            return stamp;
        }
