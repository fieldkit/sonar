#ifndef FK_CHECK_H_INCLUDED
#define FK_CHECK_H_INCLUDED

#include <leds.h>

namespace fk {

class Check {
private:
    bool flashMemory();

public:
    Check();

public:
    void setup();
    bool check();
    void failed();

};

}

#endif
