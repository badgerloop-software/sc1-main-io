project(DriversLib)

add_library(drivers src/i2c.cpp)

target_include_directories(drivers PUBLIC include)

export(TARGETS drivers FILE DriversConfig.cmake)
