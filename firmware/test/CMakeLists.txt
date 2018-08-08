include(ArduinoMinimal)

set(EXTRA_CXX_FLAGS_PROJECT "-Wall -Werror")

include_directories(./)

set(SOURCE_FILES main.cpp)
set(LIBRARIES SPI Wire)

arduino(fk-sonar-test "${SOURCE_FILES}" "${LIBRARIES}")
