#include "PacketHeader.h"

// Constructor
PacketHeader::PacketHeader(uint32_t sec, uint32_t usec,
                           uint32_t capLen, uint32_t origLen)
    : ts_sec(sec), ts_usec(usec),
      capturedLength(capLen), originalLength(origLen) {}

// Getters
uint32_t PacketHeader::getSeconds() const { return ts_sec; }
uint32_t PacketHeader::getAccuracySeconds() const { return ts_usec; }
uint32_t PacketHeader::getCapturedLength() const { return capturedLength; }
uint32_t PacketHeader::getOriginalLength() const { return originalLength; }

// Setters
void PacketHeader::setSeconds(uint32_t sec) { ts_sec = sec; }
void PacketHeader::setMicroseconds(uint32_t usec) { ts_usec = usec; }
void PacketHeader::setCapturedLength(uint32_t capLen) { capturedLength = capLen; }
void PacketHeader::setOriginalLength(uint32_t origLen) { originalLength = origLen; }