include(Arduino)

enable_arduino_toolchain()

file(GLOB sources *.cpp ../common/*.cpp)

find_package(FkModule)
find_package(RadioHead)
find_package(FuelGauge)

add_arduino_library(fk-sonar-test "${sources}")

fk_configure_module(fk-sonar-test)

target_link_libraries(fk-sonar-test RadioHead)
target_link_libraries(fk-sonar-test FuelGauge)

target_compile_options(fk-sonar-test PRIVATE -Wall -Werror)
target_include_directories(fk-sonar-test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../common")

add_arduino_firmware(fk-sonar-test)
