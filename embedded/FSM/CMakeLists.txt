project(DriversLib VERSION 0.1 LANGUAGES CXX)

add_library(FSM src/StateMachine.cpp src/Triggers.cpp src/Transitions.cpp
            src/States.cpp)

target_include_directories(FSM PUBLIC include)

export(TARGETS FSM FILE FSM.cmake)
