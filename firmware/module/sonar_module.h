#ifndef FK_SONAR_MODULE_H_INCLUDED
#define FK_SONAR_MODULE_H_INCLUDED

#include <fk-module.h>

namespace fk {

class TakeSonarReadings : public ModuleServicesState {
public:
    const char *name() const override {
        return "TakeSonarReadings";
    }

public:
    void task() override;
};

class SonarModule : public Module<MinimumFlashState> {
private:
    #ifdef FK_MODULE_WIRE11AND13
    TwoWireBus moduleBus{ Wire11and13 };
    #else
    TwoWireBus moduleBus{ Wire4and3 };
    #endif

public:
    SonarModule(ModuleInfo &info);

public:
    ModuleStates states() override {
        return {
            ModuleFsm::deferred<ConfigureModule>(),
            ModuleFsm::deferred<TakeSonarReadings>()
        };
    }
};

}

#endif
