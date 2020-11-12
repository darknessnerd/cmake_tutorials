# CMakeLists.txt
cmake_minimum_required(VERSION 3.5)
# set the project name
project(HelloWorld)

find_package(unofficial-sqlite3 CONFIG REQUIRED)


# add the executable
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::sqlite3::sqlite3)