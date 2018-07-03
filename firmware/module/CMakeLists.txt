set(SOURCE_FILES
  main.cpp
)

set(LIBRARIES
  SPI
  Wire
)

arduino(fk-sonar-module "${SOURCE_FILES}" "${LIBRARIES}")
