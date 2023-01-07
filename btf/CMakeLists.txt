add_subdirectory(googletest)

enable_testing()

add_executable(gtests
  src/gtests.cpp
  src/LogPrinter.cpp
  src/can_test.cpp
  src/gpio_test.cpp
  src/i2c_test.cpp)

if(DEFINED STUB_BUS)
    add_definitions(-DSTUB_BUS=${STUB_BUS})
endif()

target_include_directories(gtests PUBLIC include)

target_link_libraries(gtests
  gtest
  devices
  drivers)

include(GoogleTest)
