project(BTFLib)

set(dependencies src/LogPrinter.cpp
                 src/tests.cpp)

set(libraries drivers
              devices
	      pthread)
# GTest
find_package(Threads REQUIRED)
set(GTest_ROOT /usr/src/gtest)
set(GTEST_INCLUDE_DIRS ${GTest_ROOT}/include)
set(GTEST_LIBRARIES ${GTest_ROOT}/$ENV{GLIB_PATH}) # defined in bloop-dev
include_directories(${GTEST_INCLUDE_DIRS})


# BTF Libarary
add_library(btf ${dependencies})
target_include_directories(btf PUBLIC include)
target_link_libraries(btf ${libaries})
export(TARGETS btf FILE BTFConfig.cmake)

# Run all tests binary
# No export needed for executables
add_executable(tests ${dependencies})
target_include_directories(tests PUBLIC include)
target_link_libraries(tests ${GTEST_LIBRARIES} ${libraries})
