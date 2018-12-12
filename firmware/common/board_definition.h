#ifndef FK_BOARD_DEFINITION_H_INCLUDED
#define FK_BOARD_DEFINITION_H_INCLUDED

#include "board.h"

namespace fk {

extern Board board;

constexpr uint8_t FK_SONAR_PIN_PERIPH_ENABLE = 8;
constexpr uint8_t FK_SONAR_PIN_RADIO_CS = 5;
constexpr uint8_t FK_SONAR_PIN_RADIO_DIO0 = 2;
constexpr uint8_t FK_SONAR_PIN_FLASH_CS = 6;

}

#endif
