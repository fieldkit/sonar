include(Arduino)

enable_arduino_toolchain()

set(sources main.cpp)

find_package(FkModule)
find_package(RadioHead)
find_package(FuelGauge)

add_arduino_library(fk-sonar-test "${sources}")

fk_configure_module(fk-sonar-test)

target_link_libraries(fk-sonar-test RadioHead)
target_link_libraries(fk-sonar-test FuelGauge)

target_compile_options(fk-sonar-test PRIVATE -Wall -Werror)

add_arduino_firmware(fk-sonar-test)
