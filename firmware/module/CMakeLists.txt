include(ArduinoMinimal)

set(EXTRA_CXX_FLAGS_PROJECT "-Wall -Werror")

# Get the current working branch
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND git log -1 --format=%H
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_definitions("-DFIRMWARE_GIT_HASH=\"${GIT_COMMIT_HASH}\"")
add_definitions("-DFIRMWARE_GIT_BRANCH=\"${GIT_BRANCH}\"")
add_definitions("-DFIRMWARE_BUILD=\"$ENV{BUILD_TAG}\"")

file(GLOB SOURCE_FILES *.cpp)
set(LIBRARIES SPI Wire)

arduino(fk-sonar-standard "${SOURCE_FILES}" "${LIBRARIES}")

add_definitions(-DPHYLUM_ENABLE_SERIAL_FLASH -DPHYLUM_ENABLE_SD)
target_compile_options(arduino_zero_phylum PUBLIC -DPHYLUM_ENABLE_SERIAL_FLASH -DPHYLUM_ENABLE_SD)
