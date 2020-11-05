# Introduction

Shows a very basic hello world example.
The files in this tutorial are below:

```
E:\workspace_personal\cmake_tutorial\01-basic 
λ tree
E:.
├── CMakeLists.txt
├── main.cpp
```

CMakeLists.txt - Contains the CMake commands that cmake run
main.cpp - A simple "Hello World" cpp file.

# Concepts

## CMakeLists.txt

CMakeLists.txt is the file which should store all the CMake commands. When cmake is run in 
a folder it will look for this file and if it does not exist cmake will exit with an error.

## Minimum CMake

When creating a project using CMake, you can specify the minimum 
version of CMake that is supported.

```
cmake_minimum_required(VERSION 3.5)
```

## Projects

A CMake build can include a project name to make referencing 
certain variables easier when using multiple projects.

```
project (HelloWorld)
```

## Creating an Executable
The add_executable() command specifies that an executable should be build from
 the specified source files, in this example main.cpp. 
 The first argument to the add_executable() function is the name of the executable to be built,
  and the second argument is the list of source files to compile.

```
add_executable(hello_cmake main.cpp)
```

### Tips:
A shorthand that some people use is to have the project name and executable name the same. 
This allows you to specify the CMakeLists.txt as follows,
```
cmake_minimum_required(VERSION 3.5)
project (hello_cmake)
add_executable(${PROJECT_NAME} main.cpp)
```
In this example, the project() function, will create a variable ${PROJECT_NAME}
with the value hello_cmake. This can then be passed to the add_executable() function 
to output a 'hello_cmake' executable.


## Binary Directory
The root or top level folder that you run the cmake command from is known as your 
CMAKE_BINARY_DIR and is the root folder for all your binary files. CMake supports building 
and generating your binary files both in-place and also out-of-source.

### In-Place Build
In-place builds generate all temporary build files in the same directory structure as the
 source code.
This means that all Makefiles and object files are interspersed with your normal code.
 To create an in-place build target run the cmake command in your root directory. 
 For example:

```
cmake -G "MinGW Makefiles"
 -- The C compiler identification is GNU 8.1.0
 -- The CXX compiler identification is GNU 8.1.0
 -- Detecting C compiler ABI info
 -- Detecting C compiler ABI info - done
 -- Check for working C compiler: C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/gcc.exe - skipped
 -- Detecting C compile features
 -- Detecting C compile features - done
 -- Detecting CXX compiler ABI info
 -- Detecting CXX compiler ABI info - done
 -- Check for working CXX compiler: C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/g++.exe - skipped
 -- Detecting CXX compile features
 -- Detecting CXX compile features - done
 -- Configuring done
 -- Generating done
 -- Build files have been written to: E:/workspace_personal/cmake_tutorial/01-basic

make 
Scanning dependencies of target HelloWorld
[ 50%] Building CXX object CMakeFiles/HelloWorld.dir/main.cpp.obj
[100%] Linking CXX executable HelloWorld.exe
[100%] Built target HelloWorld

./HelloWorld.exe
Hello CMake!
```

## Out-of-Source Build
Out-of-source builds allow you to create a single build folder that can be anywhere on your file system. All temporary build and object files are located in this directory keeping your source tree clean. To create an out-of-source build run the cmake command in the build folder and point it to the directory with your root CMakeLists.txt file. Using out-of-source builds if you want to recreate your cmake environment from scratch, you only need to delete your build directory and then rerun cmake.

For example:
```
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
-- The C compiler identification is GNU 8.1.0
-- The CXX compiler identification is GNU 8.1.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/gcc.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/g++.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: E:/workspace_personal/cmake_tutorial/01-basic/build

make
Scanning dependencies of target HelloWorld
[ 50%] Building CXX object CMakeFiles/HelloWorld.dir/main.cpp.obj
[100%] Linking CXX executable HelloWorld.exe
[100%] Built target HelloWorld

./HelloWorld.exe
Hello CMake!

```
