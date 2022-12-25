add_subdirectory(googletest)

enable_testing()

add_executable(gtests
  include/gtest_globals.h
  src/gtests.cpp
  src/LogPrinter.cpp
  src/can_test.cpp)

target_include_directories(gtests PUBLIC include)

target_link_libraries(gtests
  devices
  drivers
  gtest)

include(GoogleTest)
