cmake_minimum_required(VERSION 3.10)

project(PodEmbeddedBeta)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(embedded/devices)
add_subdirectory(embedded/drivers)
add_subdirectory(btf)


# Creating the binary
set(dependencies main.cpp)
set(libraries devices
              drivers
              btf)

add_executable(badgerloop main.cpp ${dependecies})
target_link_libraries(badgerloop PRIVATE ${libraries})
