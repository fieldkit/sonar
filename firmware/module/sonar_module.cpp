#include "sonar_module.h"
#include "readings.h"

namespace fk {

SonarModule::SonarModule(ModuleInfo &info)
    : Module(moduleBus, info) {
}

void TakeSonarReadings::task() {
    SonarReadings readings;

    readings.setup();

    auto reading = readings.reading();
    auto i = 0;
    services().readings->done(i++, reading.value);
    services().readings->done(i++, reading.voltage);
    services().readings->done(i++, reading.distance);
    services().readings->done(i++, reading.depth);
    services().readings->done(i++, reading.mounted);

    transit<ModuleIdle>();
}

}
