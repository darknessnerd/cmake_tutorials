cmake_minimum_required(VERSION 3.5)
# set the project name
project(HelloWorld)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    main.cpp
)

# include the file with the function then call the macro
include(${CMAKE_SOURCE_DIR}/cmake/analysis.cmake)
add_analysis(${PROJECT_NAME} SOURCES)


# add the executable
add_executable(${PROJECT_NAME}  ${SOURCES})
