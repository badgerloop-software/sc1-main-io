project(DevicesLib)

add_library(devices src/mcp23017.cpp)

target_include_directories(devices PUBLIC include)
target_link_libraries(devices drivers)

export(TARGETS devices FILE DevicesConfig.cmake)
