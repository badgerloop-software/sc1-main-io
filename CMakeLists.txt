cmake_minimum_required(VERSION 3.1)

project(PodEmbeddedBeta VERSION 0.1)

OPTION(TEST "Enable test wrapper" OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)
set(ENV{PROJECT_ROOT_DIRECTORY} ${PROJECT_SOURCE_DIR}/../)
set(CMAKE_CXX_STANDARD 11)

# Run Autocoder when CMake is run
execute_process(COMMAND bash ${PROJECT_SOURCE_DIR}/bloop-dev autocode)

add_subdirectory(embedded/devices)
add_subdirectory(embedded/drivers)

IF(TEST)
    ADD_DEFINITIONS(-DTEST)
    set(dependecies tests.cpp)
ELSE()
     set(dependecies main.cpp)
ENDIF()

set(libraries devices
    drivers)

add_executable(badgerloop ${dependecies})
target_link_libraries(badgerloop PRIVATE ${libraries})

if( MATCHES "Linux")
    add_subdirectory(Test)
    setup_target_for_coverage_gcovr_html(NAME pod_coverage
                                         EXECUTABLE /out/run_all_tests
                                        )
endif()
