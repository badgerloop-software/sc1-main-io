project(DriversLib VERSION 0.1 LANGUAGES CXX)

add_library(drivers src/i2c.cpp
    src/adc128.cpp)

target_include_directories(drivers PUBLIC include)

export(TARGETS drivers FILE DriversConfig.cmake)
