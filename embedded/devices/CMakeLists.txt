project(DevicesLib VERSION 0.1 LANGUAGES CXX)

add_library(devices src/mcp23017.cpp)

target_include_directories(devices PUBLIC include)
target_link_libraries(devices PUBLIC drivers)

export(TARGETS devices FILE DevicesConfig.cmake)
