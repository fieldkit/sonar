#include <fk-module.h>

#include "sonar_module.h"

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
