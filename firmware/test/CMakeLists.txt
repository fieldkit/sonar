set(SOURCE_FILES
  main.cpp
)

set(LIBRARIES
  SPI
  Wire
)

include_directories(./)

arduino(fk-sonar-test "${SOURCE_FILES}" "${LIBRARIES}")
