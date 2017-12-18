#include <Arduino.h>
#include <FuelGauge.h>
#include <Wire.h>
#include <SPI.h>
#include <RH_RF95.h>
#include <SerialFlash.h>

const uint8_t PIN_RADIO_CS = 5;
const uint8_t PIN_RADIO_DIO0 = 2;
const uint8_t PIN_FLASH_CS = 4;

class Check {
private:
    const char * id2chip(const unsigned char *id) {
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

public:
    void setup() {
        pinMode(13, OUTPUT);
        pinMode(A3, OUTPUT);
        pinMode(A4, OUTPUT);
        pinMode(A5, OUTPUT);

        digitalWrite(13, HIGH);
        digitalWrite(A3, HIGH);
        digitalWrite(A4, HIGH);
        digitalWrite(A5, HIGH);

        pinMode(PIN_FLASH_CS, INPUT_PULLUP);
        pinMode(PIN_RADIO_CS, INPUT_PULLUP);

        pinMode(PIN_FLASH_CS, OUTPUT);
        pinMode(PIN_RADIO_CS, OUTPUT);

        digitalWrite(PIN_FLASH_CS, HIGH);
        digitalWrite(PIN_RADIO_CS, HIGH);

        SPI.begin();
    }

    void fuelGauge() {
        FuelGauge gauge;

        Serial.println("test: Checking gauge...");

        Wire.begin();

        gauge.powerOn();

        Serial.println("test: Gauge PASSED");
    }

    void flashMemory() {
        Serial.println("test: Checking flash memory...");

        if (!SerialFlash.begin(PIN_FLASH_CS)) {
            Serial.println("test: Flash memory FAILED");
            return;
        }

        uint8_t buffer[256];

        SerialFlash.readID(buffer);
        if (buffer[0] == 0) {
            Serial.println("test: Flash memory FAILED");
            return;
        }

        uint32_t chipSize = SerialFlash.capacity(buffer);
        if (chipSize == 0) {
            Serial.println("test: Flash memory FAILED");
            return;
        }

        Serial.println("Read Chip Identification:");
        Serial.print("  JEDEC ID:     ");
        Serial.print(buffer[0], HEX);
        Serial.print(" ");
        Serial.print(buffer[1], HEX);
        Serial.print(" ");
        Serial.println(buffer[2], HEX);
        Serial.print("  Part Nummber: ");
        Serial.println(id2chip(buffer));
        Serial.print("  Memory Size:  ");
        Serial.print(chipSize);
        Serial.println(" bytes");
        Serial.print("  Block Size:   ");
        uint32_t blockSize = SerialFlash.blockSize();
        Serial.print(blockSize);
        Serial.println(" bytes");

        Serial.println("test: Flash memory PASSED");
    }

    void radio() {
        Serial.println("test: Checking radio...");

        RH_RF95 rf95(PIN_RADIO_CS, PIN_RADIO_DIO0);

        if (!rf95.init()) {
            Serial.println("test: Radio FAILED");
        }
        else {
            digitalWrite(PIN_RADIO_CS, HIGH);

            Serial.println("test: Radio PASSED");
        }
    }
};

void setup() {
    Serial.begin(115200);

    Check check;
    check.setup();

    while (!Serial && millis() < 2 * 1000) {
        delay(100);
    }

    delay(100);

    check.flashMemory();
    check.radio();
    check.fuelGauge();

    while (true) {
        delay(100);
    }
}

void loop() {

}
