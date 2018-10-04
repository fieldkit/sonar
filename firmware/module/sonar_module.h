#ifndef FK_SONAR_MODULE_H_INCLUDED
#define FK_SONAR_MODULE_H_INCLUDED

#include <fk-module.h>

class TakeSonarReadings : public fk::ModuleServicesState {
public:
    const char *name() const override {
        return "TakeSonarReadings";
    }

public:
    void task() override;
};

class SonarModule : public fk::Module<fk::MinimumFlashState> {
private:
    #ifdef FK_MODULE_WIRE11AND13
    fk::TwoWireBus moduleBus{ fk::Wire11and13 };
    #else
    fk::TwoWireBus moduleBus{ fk::Wire4and3 };
    #endif

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

#endif
