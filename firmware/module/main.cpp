#include <fk-module.h>

class SonarModule : public fk::Module {
private:
    fk::TwoWireBus bus{ Wire };

public:
    SonarModule(fk::ModuleInfo &info);

public:
    fk::ModuleReadingStatus beginReading(fk::PendingSensorReading &pending) override;
};

SonarModule::SonarModule(fk::ModuleInfo &info) : Module(bus, info) {
}

fk::ModuleReadingStatus SonarModule::beginReading(fk::PendingSensorReading &pending) {
    auto DistanceFromWaterBedInMeters = 1.0f;
    auto started = millis();
    auto value = analogRead(A1);
    auto voltage = value * (3.3f / 1024.0f);
    auto distance = voltage * (1000.0f / 3.2f);
    auto depth = DistanceFromWaterBedInMeters - (distance / 100.0);
    auto elapsed = millis() - started;

    auto readings = pending.readings;
    auto i = 0;
    readings[i++].value = distance;
    readings[i++].value = depth;
    readings[i++].value = DistanceFromWaterBedInMeters;

    pending.elapsed -= millis();

    for (auto j = 0; j < i; ++j) {
        readings[j].status = fk::SensorReadingStatus::Done;
        readings[j].time = fk::clock.getTime();
    }

    return fk::ModuleReadingStatus();
}

extern "C" {

void setup() {
    Serial.begin(115200);

    while (!Serial) {
        delay(100);
    }

    firmware_version_set(FIRMWARE_GIT_HASH);
    firmware_build_set(FIRMWARE_BUILD);
    firmware_compiled_set(DateTime(__DATE__, __TIME__).unixtime());

    loginfof("Module", "Starting (%d free)", fk_free_memory());

    fk::SensorInfo sensors[3] = {
        { "distance", "m" },
        { "depth", "m" },
        { "total", "m" },
    };

    fk::SensorReading readings[3];

    fk::ModuleInfo info = {
        fk_module_ModuleType_SENSOR,
        8,
        3,
        1,
        "Sonar",
        "fk-sonar",
        sensors,
        readings
    };

    SonarModule module(info);

    module.begin();

    while(true) {
        module.tick();
        delay(10);
    }
}

void loop() {
}

}
