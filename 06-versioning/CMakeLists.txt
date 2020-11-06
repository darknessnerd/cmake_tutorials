# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project(helloWorld VERSION 1.0)
message("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")
message("helloWorld_VERSION = ${helloWorld_VERSION}")
configure_file(Version.h.in ${PROJECT_BINARY_DIR}/include/Version.h)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/Hello.cpp
    src/main.cpp
)

# Add an executable with the above sources
add_executable(helloWorld ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(helloWorld
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# include the directory with the new files
target_include_directories( helloWorld
    PUBLIC
        ${CMAKE_BINARY_DIR}/include
)