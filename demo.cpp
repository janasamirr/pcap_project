#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <filesystem>
#include "PcapParser.h"
#include "TimeStamp.h"
#include "PacketRecord.h"
using namespace std;

int main()
{
    unsigned char data1[] = {0x01, 0x02, 0x03, 0x04};
    unsigned char data2[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
    TimeStamp ts1(1723543200, 123456); // arbitrary timestamp
    TimeStamp ts2(1723543210, 654321);

    PacketRecord p1( ts1,sizeof(data1), (char*)data1);
    PacketRecord p2( ts2,sizeof(data2), (char*)data2);
    vector<PacketRecord> originalPackets = {p1, p2};
    fstream file("example.pcap");
    cout << "Current working directory: " << filesystem::current_path() << endl;
    if (!file) {
        cerr << "Error: Could not create file" << endl;
        return 1;
    }
    PcapParser parser(PcapParser::micro ,"example.pcap",true);
    parser.writePacket(p1);
    
}