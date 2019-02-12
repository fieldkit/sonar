#include <SerialFlash.h>

#include "debug.h"
#include "board_definition.h"

#include "check.h"

namespace fk {

constexpr const char LogName[] = "Check";

using Log = SimpleLog<LogName>;

Check::Check() {
}

static const char *serialFlashId2Chip(const unsigned char *id) {
    if (id[0] == 0xEF) {
        // Winbond
        if (id[1] == 0x40) {
            if (id[2] == 0x14) return "W25Q80BV";
            if (id[2] == 0x15) return "W25Q16DV";
            if (id[2] == 0x17) return "W25Q64FV";
            if (id[2] == 0x18) return "W25Q128FV";
            if (id[2] == 0x19) return "W25Q256FV";
        }
    }
    if (id[0] == 0x01) {
        // Spansion
        if (id[1] == 0x02) {
            if (id[2] == 0x16) return "S25FL064A";
            if (id[2] == 0x19) return "S25FL256S";
            if (id[2] == 0x20) return "S25FL512S";
        }
        if (id[1] == 0x20) {
            if (id[2] == 0x18) return "S25FL127S";
        }
        if (id[1] == 0x40) {
            if (id[2] == 0x15) return "S25FL116K";
        }
    }
    if (id[0] == 0xC2) {
        // Macronix
        if (id[1] == 0x20) {
            if (id[2] == 0x18) return "MX25L12805D";
        }
    }
    if (id[0] == 0x20) {
        // Micron
        if (id[1] == 0xBA) {
            if (id[2] == 0x20) return "N25Q512A";
            if (id[2] == 0x21) return "N25Q00AA";
        }
        if (id[1] == 0xBB) {
            if (id[2] == 0x22) return "MT25QL02GC";
        }
    }
    if (id[0] == 0xBF) {
        // SST
        if (id[1] == 0x25) {
            if (id[2] == 0x02) return "SST25WF010";
            if (id[2] == 0x03) return "SST25WF020";
            if (id[2] == 0x04) return "SST25WF040";
            if (id[2] == 0x41) return "SST25VF016B";
            if (id[2] == 0x4A) return "SST25VF032";
        }
        if (id[1] == 0x25) {
            if (id[2] == 0x01) return "SST26VF016";
            if (id[2] == 0x02) return "SST26VF032";
            if (id[2] == 0x43) return "SST26VF064";
        }
    }
    return "(unknown chip)";
}

bool Check::flashMemory() {
    Log::info("test: Checking flash memory...");

    SerialFlashChip serialFlash;

    if (!serialFlash.begin(board.flash_cs())) {
        Log::info("test: Flash memory FAILED");
        return false;
    }

    uint8_t buffer[256];
    serialFlash.readID(buffer);
    if (buffer[0] == 0) {
        Log::info("test: Flash memory FAILED");
        return false;
    }

    auto chipSize = serialFlash.capacity(buffer);
    if (chipSize == 0) {
        Log::info("test: Flash memory FAILED");
        return false;
    }

    Log::info("Read Chip Identification:");
    Log::info("  JEDEC ID:     %x %x %x", buffer[0], buffer[1], buffer[2]);
    Log::info("  Part Nummber: %s", serialFlashId2Chip(buffer));
    Log::info("  Memory Size:  %lu bytes Block Size: %lu bytes", chipSize, serialFlash.blockSize());

    if (false) {
        serialFlash.eraseAll();
        while (!serialFlash.ready()) {
            Log::info("test: Flash erasing...");
            delay(500);
        }
    }

    Log::info("test: Flash memory PASSED");

    return true;
}

void Check::setup() {
}

bool Check::check() {
    auto failures = false;
    if (!flashMemory()) {
        failures = true;
    }
    return !failures;
}

void Check::failed() {
    while (true) {
        // hw->leds(false);
        delay(100);
        // hw->leds(true);
        delay(100);
    }
}

}
