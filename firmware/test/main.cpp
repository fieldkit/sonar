#include <Wire.h>
#include <SPI.h>

#include <alogging/alogging.h>

#include <rtc.h>
#include <debug.h>
#include <platform.h>
#include <board_definition.h>
#include <tuning.h>

#include "check.h"
#include "readings.h"

using namespace fk;

constexpr const char LogName[] = "TEST";

using Log = SimpleLog<LogName>;

void setup() {
    Serial.begin(115200);

    board.disable_everything();

    while (!Serial && millis() < 2000) {
        delay(100);
    }

    Log::info("test: Setup");

    board.enable_everything();

    clock.begin();

    Check check;
    check.setup();
    if (!check.check()) {
        Log::info("test: FAILED");
        check.failed();
    }
    else {
        Log::info("test: PASSED");
    }

    Leds leds;

    uint32_t tick = fk_uptime();

    while (true) {
        if (fk_uptime() - tick > 1000) {
            SonarReadings readings;
            auto reading = readings.reading();

            Log::info("raw = %lu voltage = %f distance = %f depth = %f mounted = %f",
                      reading.value,
                      reading.voltage,
                      reading.distance,
                      reading.depth,
                      reading.mounted);
            tick = fk_uptime();
        }

        delay(100);
    }
}

void loop() {

}
