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

* CMakeLists.txt  - Contains the CMake commands you wish to run.
* include/Hello.h - The header file to include.
* src/Hello.cpp   - A source file to compile.
* src/main.cpp    - The source file with main.

# Concepts

## Adding a Version Number and Configured Header File

The first feature we will add is to provide our executable and project with a version number.
While we could do this exclusively in the source code, using CMakeLists.txt provides more flexibility.
First, modify the CMakeLists.txt file to use the project() command to set the project name and version number.
Set the project name and version:

```
project(HelloWorld VERSION 1.0)
```

Then, configure a header file to pass the version number to the source code:

```
configure_file(Version.h.in Version.h)
```

Since the configured file will be written into the binary tree, we must add 
that directory to the list of paths to search for include files. Add the following 
lines to the end of the CMakeLists.txt file:

```
target_include_directories(HelloWorld PUBLIC "${PROJECT_BINARY_DIR}" )
```

Using your favorite editor, create Version.h.in in the source directory with the following contents:

```
// the configured options and settings for Tutorial
#define HelloWorld_VERSION_MAJOR @HelloWorld_VERSION_MAJOR@
#define HelloWorld_VERSION_MINOR @HelloWorld_VERSION_MINOR@
```

When CMake configures this header file the values for @HelloWorld_VERSION_MAJOR@ and @HelloWorld_VERSION_MINOR@
will be replaced.
Next modify Hello.cpp to include the configured header file, Version.h.
Finally, let’s print out the executable name and version number by updating Hello.cpp as follows:

```
// report version
std::cout << " Version " << HelloWorld_VERSION_MAJOR << "." << HelloWorld_VERSION_MINOR << std::endl;  
```

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