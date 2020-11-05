# Introduction

Shows a hello world example which uses a different folder
for source and include files.

The files in this tutorial include:
```
.
├── CMakeLists.txt
├── include
│   └── Hello.h
└── src
    ├── Hello.cpp
    └── main.cpp
```

CMakeLists.txt  - Contains the CMake commands you wish to run.
include/Hello.h - The header file to include.
src/Hello.cpp   - A source file to compile.
src/main.cpp    - The source file with main.


# Concepts
## Directory Paths

CMake syntax specifies a number of variables which can be used to help find useful
directories in your project or source tree. Some of these include:

|Variable|Info|
|:--------|:----|
|CMAKE_SOURCE_DIR|The root source directory|
|CMAKE_CURRENT_SOURCE_DIR|The current source directory if using sub-projects and directories.|
|PROJECT_SOURCE_DIR|The source directory of the current cmake project.|
|CMAKE_BINARY_DIR|The root binary / build directory. This is the directory where you ran the cmake command.|
|CMAKE_CURRENT_BINARY_DIR|The build directory you are currently in.|
|PROJECT_BINARY_DIR|The build directory for the current project.|


## Source Files Variable
Creating a variable which includes the source files allows you to be clearer about these files and 
easily add them to multiple commands, for example, the add_executable() function.

```
# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/Hello.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
```
Notes:
> An alternative to setting specific file names in the SOURCES variable is to use a GLOB 
>command to find files using wildcard pattern matching.
>```file(GLOB SOURCES "src/*.cpp")```

Tips:
>For modern CMake it is NOT recommended to use a variable for sources. 
>Instead it is typical to directly declare the sources in the add_xxx function.

This is particularly important for glob commands which may not always show you the correct results if you add a new source file.

## Including Directories
When you have different include folders, you can make your compiler aware of them using 
the target_include_directories() function. 
When compiling this target this will add these directories to the compiler with the 
-I flag e.g. -I/directory/path

```
target_include_directories(target
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
```

The PRIVATE identifier specifies the scope of the include. This is important for libraries and is
explained in the next example. More details on the function is available [here](https://cmake.org/cmake/help/v3.5/command/target_include_directories.html "Here")



## Building the Example

```
mkdir build
cd build 
λ cmake -G "MinGW Makefiles" ..
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
-- Build files have been written to: E:/workspace_personal/cmake_tutorials/02-hello-headers/build

make
Scanning dependencies of target hello_headers
[ 33%] Building CXX object CMakeFiles/hello_headers.dir/src/Hello.cpp.obj
[ 66%] Building CXX object CMakeFiles/hello_headers.dir/src/main.cpp.obj
[100%] Linking CXX executable hello_headers.exe
[100%] Built target hello_headers

./hello_headers.exe
λ .\hello_headers.exe
Hello Headers!
```
