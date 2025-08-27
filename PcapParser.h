#include <fstream>
#include <string>
#include <cstdint>
#include <iomanip>
#include "PacketRecord.h"
#include "TimeStamp.h"

using namespace std;

class PcapParser {
    public:
        enum TimeStampType{nano,micro};

    private:
        uint32_t magicNumber=0xA1B2C3D4; //little endian, seconds and microseconds
        uint16_t majorV=2;
        uint16_t minorV=4;
        const uint32_t r1=0;
        const uint32_t r2=0;
        uint32_t snapLength=65535; //max length per packet
        uint32_t linkType=1;  //1 means ethernet which is the most common
        fstream fileStream;
        string fileName;
        TimeStampType type;
        bool isLittleEndian;

    public:
        PcapParser(TimeStampType type, string fileName, bool endian);
        PcapParser(string fileName);
        void writePacket(const PacketRecord& p);
        vector<PacketRecord> readPcapFile();
        bool checkLittleEndian(uint32_t magicNumber);
};


