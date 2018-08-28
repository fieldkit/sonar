#include <fk-module.h>

class TakeSonarReadings : public fk::ModuleServicesState {
public:
    const char *name() const override {
        return "TakeSonarReadings";
    }

public:
    void task() override;
};

class SonarModule : public fk::Module {
private:
    fk::TwoWireBus bus{ Wire };

public:
    SonarModule(fk::ModuleInfo &info);

public:
    fk::ModuleStates states() override {
        return {
            fk::ModuleFsm::deferred<fk::ConfigureModule>(),
            fk::ModuleFsm::deferred<TakeSonarReadings>()
        };
    }
};

void TakeSonarReadings::task() {
    auto DistanceFromWaterBedInMeters = 1.0f;
    auto value = analogRead(A1);
    auto voltage = value * (3.3f / 1024.0f);
    auto distance = voltage * (1000.0f / 3.2f);
    auto depth = DistanceFromWaterBedInMeters - (distance / 100.0);

    auto i = 0;
    services().readings->done(i++, distance);
    services().readings->done(i++, depth);
    services().readings->done(i++, DistanceFromWaterBedInMeters);

    transit<fk::ModuleIdle>();
}

SonarModule::SonarModule(fk::ModuleInfo &info) : Module(bus, info) {
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

    loginfof("Module", "Starting (%lu free)", fk_free_memory());

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
