project(DevicesLib VERSION 0.1 LANGUAGES CXX)

add_library(devices src/mcp23017.cpp src/tca6416.cpp src/bms.cpp src/mppt.cpp src/rtc.cpp)

target_include_directories(devices PUBLIC include)
target_link_libraries(devices PUBLIC drivers)

export(TARGETS devices FILE DevicesConfig.cmake)
