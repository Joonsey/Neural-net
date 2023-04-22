cmake_minimum_required(VERSION 3.16)

project(neural_network)

# Add C++11 support
set(CMAKE_CXX_STANDARD 11)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable
add_executable(neural_network ${SOURCES})

# Add include directories
include_directories(include)
include_directories(src)

# Add libraries
# add_library(my_library STATIC ${LIBRARY_SOURCES})

# Link libraries
# target_link_libraries(neural_network my_library)

# Add compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

# Add build type
set(CMAKE_BUILD_TYPE Debug)

# Add install target
# install(TARGETS neural_network DESTINATION bin)

