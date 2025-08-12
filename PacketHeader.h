#include <cstdint>
#include "TimeStamp.h"
class PacketHeader
{
    private:
        uint32_t ts_sec;
        uint32_t ts_usec;
        uint32_t capturedLength;
        uint32_t originalLength;
    public:
        // Constructor
        PacketHeader(uint32_t sec = 0, uint32_t usec = 0,
                    uint32_t capLen = 0, uint32_t origLen = 0);

        // Getters
        uint32_t getSeconds() const;
        uint32_t getAccuracySeconds() const;
        uint32_t getCapturedLength() const;
        uint32_t getOriginalLength() const;

        // Setters
        void setTimeStamp(TimeStampType type,uint32_t sec,uint32_t usec);
        void setSeconds(uint32_t sec);
        void setMicroseconds(uint32_t usec);
        void setCapturedLength(uint32_t capLen);
        void setOriginalLength(uint32_t origLen);
    };