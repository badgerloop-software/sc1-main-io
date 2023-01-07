# This one is important
SET(CMAKE_SYSTEM_NAME BeagleBone)

# Specify the cross compiler
SET(CMAKE_C_COMPILER   /opt/gcc-arm-10.3-2021.07-aarch64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER /opt/gcc-arm-10.3-2021.07-aarch64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-g++)

# Search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# For libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
