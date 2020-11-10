cmake_minimum_required(VERSION 3.5)

# Set the project name
project (main)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/Reverse.cpp
    src/main.cpp
)

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src/include
)

#############################################
# Unit tests

add_subdirectory(3rd_party/google-test)

# enable CTest testing
enable_testing()

# Add a testing executable
add_executable(ReverseTest ReverseTest.cpp src/Reverse.cpp)

target_link_libraries(ReverseTest
    GTest::GTest 
    GTest::Main
)
target_include_directories(ReverseTest
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src/include
)

# add the test {test name} and class test 
add_test(reverse_class_test ReverseTest)