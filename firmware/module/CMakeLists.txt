include(Arduino)

enable_arduino_toolchain()

file(GLOB sources *.cpp ../common/*.cpp)

find_package(FkModule)

add_arduino_library(fk-sonar-standard "${sources}")

fk_configure_module(fk-sonar-standard)

target_compile_options(fk-sonar-standard PRIVATE -Wall -Werror)
target_include_directories(fk-sonar-standard PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../common")

add_arduino_firmware(fk-sonar-standard)
