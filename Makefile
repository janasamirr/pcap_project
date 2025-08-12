all: demo

build:
	g++ demo.cpp -std=c++17

run:
	./a.exe

demo: demo.cpp FileHeader.cpp PacketHeader.cpp
    g++ demo.cpp FileHeader.cpp PacketHeader.cpp -std=c++17 -o demo
