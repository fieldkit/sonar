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

#endif
