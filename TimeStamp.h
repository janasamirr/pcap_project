#include <cstdint>
enum struct TimeStampType
{
    MICRO,NANO
};

class TimeStamp
{
    private:
    TimeStampType type;
    uint32_t seconds;
    uint32_t accuracy;
    
    public:
    // Constructor
    TimeStamp(TimeStampType t, uint32_t s, uint32_t us);
    TimeStampType getType() const;
    uint32_t getSeconds() const;
    uint32_t getAccuracy() const;
};