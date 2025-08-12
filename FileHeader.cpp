#include "FileHeader.h"

    FileHeader::FileHeader(uint32_t magic = 0xa1b2c3d4,
               uint16_t major = 2,
               uint16_t minor = 4,
               uint32_t snapLen = 65535,
               uint32_t link = 1)
               {
               }
    uint32_t FileHeader:: getMagicNumber() const
        {
            return magicNumber;
        }
    uint16_t FileHeader:: getMajorVersion() const{
            return majorV;
        }
    uint16_t FileHeader::  getMinorVersion() const
        {
            return minorV;
        }
    uint32_t FileHeader:: getSnapLength() const
        {
            return snapLength;
        }
    uint32_t FileHeader::getLinkType() const
        {
            return linkType;
        }