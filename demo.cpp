#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iomanip>
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
    //vector<PacketRecord> originalPackets = {p1, p2};
    // fstream file("output.pcap", ios::out | ios::binary);
    // if (!file) {
    //     cerr << "Error: Could not create file" << endl;
    //     return 1;
    // }
    //file.close();
    PcapParser parser("nlmon-big.pcap"); 
    vector<PacketRecord> readPackets; 
    readPackets=parser.readPcapFile();
    cout << "PCAP file elements" << endl;

  for (size_t i = 0; i < readPackets.size(); i++) 
  {
    cout << "Packet " << i+1 << ": ";
    cout << "ts=" << dec << readPackets[i].getTimeStamp().getSeconds() << ".";
    cout << readPackets[i].getTimeStamp().getAccuracy() << " ";
    cout << "len=" << dec << readPackets[i].getLength() << endl;
    cout << "Data: ";
    for (size_t j = 0; j < readPackets[i].getLength(); j++) {
        cout << hex << setw(2) << setfill('0')
             << (unsigned int)(unsigned char)readPackets[i].getData()[j] << " ";
    }
    cout << dec << endl << endl; // reset back to decimal
  }

    //parser.writePacket(p1);    
}