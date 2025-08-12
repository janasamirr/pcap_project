#include <fstream>
#include <string>
#include <cstdint>
#include "Packet.h"       // for Packet class
#include "PacketHeader.h" // for PacketHeader struct
#include "TimeStamp.h"// for TimeStampType enum
#include "FileHeader.h"
using namespace std;

class PcapParser {
private:
    fstream fileStream;
    string fileName;
    bool isLittleEndian;
public:
    // Constructor
    PcapParser(const string& file, bool littleEndian);

    // Getter
    bool getIsLittleEndian() const;
    // Writes a packet to the pcap file
    void writePacket(const Packet& data, const TimeStamp& ts);
};


