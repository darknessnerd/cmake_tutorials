# CMakeLists.txt
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
# set the project name
project(HelloWorld)

# Included the conan build information
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)



# add the executable
add_executable(${PROJECT_NAME} main.cpp)


# link against the fmt target supplied by conan
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        CONAN_PKG::sqlite3
)