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
PcapParser::PcapParser(string fileName)
:fileName(fileName)
{
    fileStream.open(fileName, ios::in | ios::binary);
    if (!fileStream) 
    {
        throw runtime_error("Failed to open file: " + fileName);
    }
}

void PcapParser::writePacket(const PacketRecord& p) {
    if (!fileStream.is_open()) {
        throw std::runtime_error("File stream is not open: " + fileName);
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

vector<PacketRecord> PcapParser::readPcapFile()
{
    vector<PacketRecord> packets;
    fileStream.seekg(24, ios::beg);
    cout << fileStream.eof() << endl;
    cout << fileStream.good() << endl; // skip global header
    cout << fileStream.tellg() << endl;

    while (fileStream.good()) {
        uint32_t ts_sec, ts_accuracy, cap_len, orig_len;
        // Read packet header
        fileStream.read(reinterpret_cast<char*>(&ts_sec), sizeof(ts_sec));
        cout << fileStream.eof() << endl;
        cout << __LINE__ << endl;
        if (!fileStream.read(reinterpret_cast<char*>(&ts_accuracy), sizeof(ts_accuracy))) break;
        if (!fileStream.read(reinterpret_cast<char*>(&cap_len), sizeof(cap_len))) break;
        if (!fileStream.read(reinterpret_cast<char*>(&orig_len), sizeof(orig_len))) break;
        cout << __LINE__ << endl;

        cout << "Read packet header: ts=" << ts_sec << " len=" << cap_len << endl;
        if (cap_len > 65535) {
            cerr << "Invalid cap_len=" << cap_len << endl;
            break;
        }

        char* buffer = new char[cap_len];
        if (!fileStream.read(buffer, cap_len)) {
            cerr << "Unexpected end of file\n";
            break;
        }
        // Construct packet (make sure PacketRecord copies the data!)
        TimeStamp ts(ts_sec, ts_accuracy);
        PacketRecord packet(ts, cap_len, buffer); 
        packets.push_back(packet);

        cout << "Packet pushed back, size=" << packets.size() << endl;
    }

    fileStream.close();
    return packets;
}

/* vector<PacketRecord> PcapParser::readPcapFile()
{
    vector<PacketRecord> packets;
    fileStream.seekg(24, ios::beg);
    while(!fileStream.eof())
    {
        uint32_t ts_sec, ts_accuracy, cap_len, orig_len;
        fileStream.read(reinterpret_cast<char*>(&ts_sec), sizeof(ts_sec));
        cout<<"read time stamp";
        fileStream.read(reinterpret_cast<char*>(&ts_accuracy), sizeof(ts_accuracy));
        fileStream.read(reinterpret_cast<char*>(&cap_len), sizeof(cap_len));
        fileStream.read(reinterpret_cast<char*>(&orig_len), sizeof(orig_len));
        cout<<"read original length";
        //if (!fileStream) break;
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
        cout<<"packet is pushed back";
        delete[] buffer;
    }
    fileStream.close();
    return packets;
} */

