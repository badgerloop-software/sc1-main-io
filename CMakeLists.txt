cmake_minimum_required(VERSION 3.14)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

project(PodEmbeddedBeta VERSION 0.1)

OPTION(DEV "Enable test wrapper" OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)
set(ENV{PROJECT_ROOT_DIRECTORY} ${PROJECT_SOURCE_DIR}/../)
set(CMAKE_CXX_STANDARD 11)

# Run Autocoder when CMake is run
execute_process(COMMAND bash ${PROJECT_SOURCE_DIR}/bloop-dev autocode)

IF(DEV)
    ADD_DEFINITIONS(-DDEV)
    set(dependencies tests.cpp)
ELSE()
    set(dependencies main.cpp)
ENDIF()

add_subdirectory(embedded/devices)
add_subdirectory(embedded/drivers)
add_subdirectory(btf)

set(libraries devices
    drivers)

add_executable(badgerloop ${dependencies})
target_link_libraries(badgerloop PRIVATE ${libraries} pthread)

if( MATCHES "Linux")
    add_subdirectory(Test)
    setup_target_for_coverage_gcovr_html(NAME pod_coverage
                                         EXECUTABLE /out/run_all_tests
                                        )
endif()
