#include <fk-module.h>

#include "sonar_hardware.h"
#include "sonar_module.h"

extern "C" {

void setup() {
    Serial.begin(115200);

    pinMode(fk::FK_SONAR_PIN_PERIPH_ENABLE, OUTPUT);
    digitalWrite(fk::FK_SONAR_PIN_PERIPH_ENABLE, LOW);

    while (!Serial && millis() < 2000) {
        delay(100);
    }

    if (!Serial) {
        // The call to end here seems to free up some memory.
        Serial.end();
        Serial5.begin(115200);
        log_uart_set(Serial5);
    }

    digitalWrite(fk::FK_SONAR_PIN_PERIPH_ENABLE, HIGH);

    firmware_version_set(FIRMWARE_GIT_HASH);
    firmware_build_set(FIRMWARE_BUILD);
    firmware_compiled_set(DateTime(__DATE__, __TIME__).unixtime());

    loginfof("Module", "Starting (%lu free)", fk_free_memory());

    fk::SensorInfo sensors[4] = {
        { "raw", "mv" },
        { "distance", "m" },
        { "depth", "m" },
        { "total", "m" },
    };

    fk::SensorReading readings[4];

    fk::ModuleInfo info = {
        fk_module_ModuleType_SENSOR,
        8,
        4,
        3,
        "Sonar",
        "fk-sonar",
        sensors,
        readings,
        0,
        fk_module_RequiredUptime_READINGS_ONLY,
    };

    fk::SonarModule module(info);

    module.begin();

    while(true) {
        module.tick();
        delay(10);
    }
}

void loop() {
}

}
