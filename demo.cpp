#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include "FileHeader.h"
#include "PacketHeader.h"
using namespace std;

// enum class TimeStampType
// {
//     MICRO,NANO
// };

// struct TimeStamp
// {
//     uint32_t seconds;
//     uint32_t accuracy;
    

//     // Constructor
//     TimeStamp(uint32_t s, uint32_t us)
//         : seconds(s), accuracy(us) {}
// };


// struct FileHeader
// {
//     uint32_t magicNumber=0xa1b2c3d4; //little endian, seconds and microseconds
//     uint16_t majorV=2;
//     uint16_t minotV=4;
//     const uint32_t r1=0;
//     const uint32_t r2=0;
//     uint32_t snapLength=65535; //max length per packet
//     uint32_t linkType=1;  //1 means ethernet which is the most common
// };
// struct PacketHeader
// {
//     uint32_t ts_sec;
//     uint32_t ts_usec;
//     uint32_t capturedLength;
//     uint32_t originalLength;
// };

// class Packet
// {
//   private:
//     uint32_t packetLength;
//     TimeStampType timeStamp;
//     vector<uint8_t> packetData;
//   public:
//     //constructor
//     Packet(uint32_t length, TimeStampType tsType, const vector<uint8_t>& data):
//     packetLength(length), timeStamp(tsType), packetData(data)
//     {
//     }
//     //getters
//     uint32_t getLength() const 
//     { 
//         return packetLength; 
//     }
//     TimeStampType getTimeStampType() const 
//     { 
//         return timeStamp; 
//     }
//     const vector<uint8_t>& getData() const 
//     { 
//         return packetData; 
//     }

// };



// class pcapParser
// {
//   fstream fileStream;
//   string fileName;
//   bool isLittleEndian;
//   int snapLength;
//   uint32_t linkLayerType;
//   TimeStampType timestampType;

//   uint32_t getLinkLayerType() const 
//     { 
//         return linkLayerType; 
//     }

//   //pass arg by reference to avoid copying the entire thing
//   void writePacket(const Packet& data,const Packet& timeStamp)
//   {
    
//     PacketHeader header;
//     header.ts_sec = 0;      // Placeholder timestamp
//     header.ts_usec = 0;
//     header.capturedLength = data.getLength();
//     header.originalLength = data.getLength();

//     fileStream.write(reinterpret_cast<char*>(&header), sizeof(header));
//     fileStream.write(reinterpret_cast<const char*>(data.getData().data()), data.getLength());
//   }

// };



int main()
{
    ofstream out("output.pcap",ios::binary);
    if (!out) return 1;
    FileHeader fh;
    out.write(reinterpret_cast<const char*>(&fh), sizeof(fh));
    vector<uint8_t> packetData(60, 0xAB);
    PacketHeader ph {1690000000, 123456, 60, 60};
    out.write(reinterpret_cast<const char*>(&ph), sizeof(ph));
    out.write(reinterpret_cast<const char*>(packetData.data()), packetData.size());
    
    out.close();
    return 0;

    std::cout << "HI" << std::endl;
}