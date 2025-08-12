#include "PcapParser.h"
#include "TimeStamp.h"
#include "packet.h"
#include "PacketHeader.h"
#include "FileHeader.h"


PcapParser::PcapParser(const std::string& file, bool littleEndian)
    : fileName(file),
      isLittleEndian(littleEndian)
{
    fileStream.open(fileName, std::ios::out | std::ios::binary);
    if (!fileStream) {
        throw std::runtime_error("Failed to open file: " + fileName);
    }
}

bool PcapParser::getIsLittleEndian() const {   // ✅ getter definition
    return isLittleEndian;
}

void PcapParser::writePacket(const Packet& data, const TimeStamp& ts) {
    PacketHeader header{};
    header.setTimeStamp(ts.getType(),ts.getSeconds(),ts.getAccuracy()) ;
    header.setCapturedLength(data.getLength());
    header.setOriginalLength(data.getLength());

    fileStream.write(reinterpret_cast<char*>(&header), sizeof(header));
    fileStream.write(reinterpret_cast<const char*>(data.getData().data()), data.getLength());
}
