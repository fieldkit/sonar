#ifndef FK_READINGS_H_INCLUDED
#define FK_READINGS_H_INCLUDED

#include <cinttypes>

namespace fk {

class SonarReadings {
public:
    struct SonarReading {
        uint32_t value;
        float voltage;
        float distance;
        float depth;
        float mounted;
    };

public:
    SonarReading reading();

};

}

#endif
