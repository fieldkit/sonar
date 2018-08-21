include(Arduino)

enable_arduino_toolchain()

set(sources main.cpp)

find_package(FkModule)

add_arduino_library(fk-sonar-module "${sources}")

fk_configure_module(fk-sonar-module)

target_compile_options(fk-sonar-module PRIVATE -Wall -Werror)

add_arduino_firmware(fk-sonar-module)
