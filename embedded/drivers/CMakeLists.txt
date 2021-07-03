project(DriversLib VERSION 0.1 LANGUAGES CXX)

add_library(drivers src/i2c.cpp
    src/can.cpp)

target_include_directories(drivers PUBLIC include)
target_link_libraries(drivers PUBLIC devices)

export(TARGETS drivers FILE DriversConfig.cmake)
