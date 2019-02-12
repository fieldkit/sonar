#include <Arduino.h>

#include "readings.h"

namespace fk {

void SonarReadings::setup() {
    analogReadResolution(12);
}

constexpr float Vcc = 3.3f;
constexpr float VoltsPerUnit = (Vcc / 4096.0f);
constexpr float VoltsPerMm = (Vcc / 10240.0f);
constexpr float CmPerUnit = 1.0f / 4.0f;
constexpr float MountedDistanceInCm = 100.0f;

SonarReadings::SonarReading SonarReadings::reading() {
    auto mounted = MountedDistanceInCm;
    auto value = analogRead(A1);
    auto voltage = value * VoltsPerUnit;
    auto distance = value * CmPerUnit;
    auto depth = mounted - distance;

    return {
        value,
        voltage,
        distance,
        depth,
        mounted
    };
}

}
