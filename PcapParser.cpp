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


bool PcapParser::checkLittleEndian(uint32_t magicNumber)
{
    if(magicNumber==0xa1b2c3d4)
        return true;
    else if(magicNumber==0xa1b23c4d)
        return true;
    else if(magicNumber==0xd4c3b2a1)
        return false;
    else return false;
}

uint32_t swap32(uint32_t val) {
    return ((val & 0xFF000000) >> 24) |  // move byte 4 → 1
           ((val & 0x00FF0000) >> 8)  |  // move byte 3 → 2
           ((val & 0x0000FF00) << 8)  |  // move byte 2 → 3
           ((val & 0x000000FF) << 24);   // move byte 1 → 4
}

vector<PacketRecord> PcapParser::readPcapFile()
{
    vector<PacketRecord> packets;
    fileStream.read(reinterpret_cast<char*>(&magicNumber), sizeof(magicNumber));
    if(!fileStream)
    {
        cerr << "Invalid magic number" <<endl;
    }
    cout<<"magic number="<<magicNumber<<endl;
    
    isLittleEndian=checkLittleEndian(magicNumber);
    fileStream.seekg(20, ios::cur);
    uint32_t ts_sec, ts_accuracy, cap_len, orig_len;
    if(checkLittleEndian(magicNumber))
    {
    char* buffer;
    while (fileStream.good()) {
        
        // Read packet header
        if (!fileStream.read(reinterpret_cast<char*>(&ts_sec), sizeof(ts_sec)))break;
        if (!fileStream.read(reinterpret_cast<char*>(&ts_accuracy), sizeof(ts_accuracy))) break;
        if (!fileStream.read(reinterpret_cast<char*>(&cap_len), sizeof(cap_len))) break;
        if (!fileStream.read(reinterpret_cast<char*>(&orig_len), sizeof(orig_len))) break;
        if (cap_len > 65535) {
            cerr << "Invalid cap_len=" << cap_len << endl;
            break;
        }
        cout << "Read packet header: ts=" << ts_sec << "." << ts_accuracy << endl;
        cout << "captured packet length = "<< cap_len <<endl;
        

        buffer = new char[cap_len];
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
    delete[] buffer;
    buffer=nullptr;
    return packets;
    }
    else if (!checkLittleEndian(magicNumber))
    {
        char* buffer;
        while(fileStream.good())
        {
            if (!fileStream.read(reinterpret_cast<char*>(&ts_sec), sizeof(ts_sec)))break;   
            ts_sec= swap32(ts_sec);  
            if (!fileStream.read(reinterpret_cast<char*>(&ts_accuracy), sizeof(ts_accuracy))) break;
            ts_accuracy= swap32(ts_accuracy);
            if (!fileStream.read(reinterpret_cast<char*>(&cap_len), sizeof(cap_len))) break;
            cap_len= swap32(cap_len);     
            if (!fileStream.read(reinterpret_cast<char*>(&orig_len), sizeof(orig_len))) break;       
            orig_len= swap32(orig_len);

            if (cap_len > 65535) {
            cerr << "Invalid cap_len=" << cap_len << endl;
            break;
            }

            cout << "Read packet header: ts=" << ts_sec << "." << ts_accuracy << endl;
            cout << "captured packet length = "<< cap_len <<endl;

            buffer= new char[cap_len];

            if (!fileStream.read(buffer, cap_len)) {
            cerr << "Unexpected end of file\n";
            delete[] buffer;   
            break;
            }

            TimeStamp ts(ts_sec, ts_accuracy);
            PacketRecord packet(ts, cap_len, buffer); 
            packets.push_back(packet);   
            cout << "Packet pushed back, size=" << packets.size() << endl;
        }
        fileStream.close();
        delete[] buffer;
        buffer=nullptr;
        return packets;

    }
}

