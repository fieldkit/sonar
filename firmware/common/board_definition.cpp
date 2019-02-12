#include "board_definition.h"

namespace fk {

Board board{
    {
        FK_SONAR_PIN_PERIPHERALS_ENABLE,
        FK_SONAR_PIN_FLASH_CS,
        {
            FK_SONAR_PIN_FLASH_CS,
            0,
            0,
            0,
        },
        {
            FK_SONAR_PIN_PERIPHERALS_ENABLE,
            0,
            0,
            0,
        }
    }
};

}
