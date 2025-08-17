#include "PcapParser.h"

PcapParser::PcapParser(TimeStampType type, string fileName, bool endian)
    : fileName(fileName),type(type),isLittleEndian(endian)
{   
    fileStream.open(fileName, ios::out | ios::binary);
    if (!fileStream) {
        throw std::runtime_error("Failed to open file: " + fileName);
    }
    if(type==TimeStampType::micro)
        magicNumber=0xA1B2C3D4;
    else 
        magicNumber=0xA1B23C4D;
    fileStream.write(reinterpret_cast<const char*>(&magicNumber), sizeof(magicNumber));
    fileStream.write(reinterpret_cast<const char*>(&majorV), sizeof(majorV));
    fileStream.write(reinterpret_cast<const char*>(&minorV), sizeof(minorV));
    fileStream.write(reinterpret_cast<const char*>(&r1), sizeof(r1));
    fileStream.write(reinterpret_cast<const char*>(&r2), sizeof(r2));
    fileStream.write(reinterpret_cast<const char*>(&snapLength), sizeof(snapLength));
    fileStream.write(reinterpret_cast<const char*>(&linkType), sizeof(linkType));   
}

void PcapParser::writePacket(const PacketRecord p) {
    fileStream.open(fileName, ios::out | ios::binary);
    if (!fileStream) {
        throw std::runtime_error("Failed to open file: " + fileName);
    }
    TimeStamp ts = p.getTimeStamp();
    uint32_t ts_sec  = ts.getSeconds();
    uint32_t ts_accuracy = ts.getAccuracy();
    uint32_t dataLength = p.getLength();
    fileStream.write(reinterpret_cast<char*>(&ts_sec), sizeof(ts_sec));
    fileStream.write(reinterpret_cast<char*>(&ts_accuracy), sizeof(ts_accuracy));
    fileStream.write(reinterpret_cast<char*>(&dataLength), sizeof(dataLength));
    fileStream.write(reinterpret_cast<char*>(&dataLength), sizeof(dataLength));
    fileStream.write(p.getData(), dataLength);    
}


vector<PacketRecord> PcapParser::readPacket(const string& fileName)
{
    vector<PacketRecord> packets;
    fstream fileStream(fileName, ios::binary);
    if (!fileStream) {
        throw runtime_error("Failed to open file for reading: " + fileName);
    }
    fileStream.seekg(24, ios::beg);
    while (true) 
    {
        uint32_t ts_sec, ts_accuracy, cap_len, orig_len;
        fileStream.read(reinterpret_cast<char*>(&ts_sec), sizeof(ts_sec));
        fileStream.read(reinterpret_cast<char*>(&ts_accuracy), sizeof(ts_accuracy));
        fileStream.read(reinterpret_cast<char*>(&cap_len), sizeof(cap_len));
        fileStream.read(reinterpret_cast<char*>(&orig_len), sizeof(orig_len));
        if (!fileStream) break;
        char* buffer = new char[cap_len]; //Allocate a raw buffer for the packet payload (size = incl_len).
        fileStream.read(buffer,cap_len);
        if(!fileStream)
        {
            delete[] buffer; 
            break; 
        }
        TimeStamp ts(ts_sec, ts_accuracy);
        PacketRecord packet(ts,cap_len, buffer);
        packets.push_back(packet);
        delete[] buffer;
    }
    fileStream.close();
    return packets;

}
