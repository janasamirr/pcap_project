CXX = g++
CXXFLAGS = -std=c++17 -Wall

TARGET = demo
SRCS = demo.cpp TimeStamp.cpp PacketRecord.cpp PcapParser.cpp
OBJS = demo.o TimeStamp.o PacketRecord.o PcapParser.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

demo.o: demo.cpp
	$(CXX) $(CXXFLAGS) -c demo.cpp

TimeStamp.o: TimeStamp.cpp
	$(CXX) $(CXXFLAGS) -c TimeStamp.cpp

PacketRecord.o: PacketRecord.cpp
	$(CXX) $(CXXFLAGS) -c PacketRecord.cpp

PcapParser.o: PcapParser.cpp
	$(CXX) $(CXXFLAGS) -c PcapParser.cpp

clean:
	del $(OBJS) $(TARGET).exe
