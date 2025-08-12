#include "FileHeader.h"

    FileHeader::FileHeader(uint32_t magic,
                       uint16_t major,
                       uint16_t minor,
                       uint32_t snapLen,
                       uint32_t link)
    : magicNumber(magic),
      majorV(major),
      minorV(minor),
      snapLength(snapLen),
      linkType(link) {}
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