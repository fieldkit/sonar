include(Arduino)

enable_arduino_toolchain()

file(GLOB sources *.cpp)

find_package(FkModule)

add_arduino_library(fk-sonar-standard "${sources}")

fk_configure_module(fk-sonar-standard)

target_compile_options(fk-sonar-standard PRIVATE -Wall -Werror)

add_arduino_firmware(fk-sonar-standard)
