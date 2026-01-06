cmake_minimum_required(VERSION 3.10)
project(VehicleRentalSystem)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
)

# Executable
add_executable(VehicleRentalSystem ${SOURCES})

if(MINGW)
    target_link_options(${PROJECT_NAME} PRIVATE "-static-libgcc" "-static-libstdc++")
    # target_link_options(${PROJECT_NAME} PRIVATE "-Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
endif()

# Copy data.txt to the build directory so the executable can find it
configure_file(src/data.txt data.txt COPYONLY)
