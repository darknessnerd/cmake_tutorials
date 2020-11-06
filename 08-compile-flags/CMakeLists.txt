cmake_minimum_required(VERSION 3.5)


# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set a default C++ compile flag
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)

# Set the project name
project (hello_flags)

# Add an executable
add_executable(hello_flags_bin main.cpp)



target_compile_definitions(hello_flags_bin 
    PRIVATE EX3
)