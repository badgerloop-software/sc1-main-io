project(BTFLib)

set(dependencies src/LogPrinter.cpp
                 src/tests.cpp)

set(libraries drivers
              devices
	      pthread)
# GTest
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# BTF Libarary
add_library(btf ${dependencies})
target_include_directories(btf PUBLIC include)
target_link_libraries(btf PUBLIC ${libaries})
export(TARGETS btf FILE BTFConfig.cmake)

# Run all tests binary
add_executable(tests ${dependencies})
target_include_directories(tests PUBLIC include)
target_link_libraries(tests ${GTEST_LIBRARIES} ${libraries})
