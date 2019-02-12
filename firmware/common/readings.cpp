#include <Arduino.h>

#include "readings.h"

namespace fk {

SonarReadings::SonarReading SonarReadings::reading() {
    auto mounted = 1.0f;
    auto value = analogRead(A1);
    auto voltage = value * (3.3f / 1024.0f);
    auto distance = voltage * (1000.0f / 3.2f);
    auto depth = mounted - (distance / 100.0f);

    return {
        value,
        voltage,
        distance,
        depth,
        mounted
    };
}

}
