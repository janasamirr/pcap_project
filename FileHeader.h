#include <cstdint>
struct FileHeader
{   private:
        uint32_t magicNumber=0xa1b2c3d4; //little endian, seconds and microseconds
        uint16_t majorV=2;
        uint16_t minorV=4;
        const uint32_t r1=0;
        const uint32_t r2=0;
        uint32_t snapLength=65535; //max length per packet
        uint32_t linkType=1;  //1 means ethernet which is the most common

    public:
        FileHeader(uint32_t magic = 0xa1b2c3d4,
               uint16_t major = 2,
               uint16_t minor = 4,
               uint32_t snapLen = 65535,
               uint32_t link = 1);
        uint32_t getMagicNumber() const;
        uint16_t getMajorVersion() const;
        uint16_t getMinorVersion() const;
        uint32_t getSnapLength() const;
        uint32_t getLinkType() const;


};