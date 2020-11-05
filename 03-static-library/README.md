Introduction

Shows a hello world example which first creates and links a static library. 
This is a simplified example showing the library and binary in the same folder. 
Typically these would be in sub-projects as described in in another tutorial.

The files in this tutorial are below:
```
$ tree
.
├── CMakeLists.txt
├── include
│   └── static
│       └── Hello.h
└── src
    ├── Hello.cpp
    └── main.cpp
```
CMakeLists.txt - Contains the CMake commands you wish to run
include/static/Hello.h - The header file to include
src/Hello.cpp - A source file to compile
src/main.cpp - The source file with main

# Concepts
## Adding a Static Library
The add_library() function is used to create a library from some source files. This is called as follows:

```
add_library(hello_library STATIC
    src/Hello.cpp
)
```

This will be used to create a static library with the name libhello_library.a with the sources in the add_library call.

Note
> As mentioned in the previous example, we pass the source files directly to the add_library call, as recommended for modern CMake.

## Populating Including Directories

In this example, we include directories in the library using the target_include_directories() function with the scope set to PUBLIC.

```
target_include_directories(hello_library
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
```

This will cause the included directory used in the following places:
* When compiling the library
* When compiling any additional target that links the library.

The meaning of scopes are:
* PRIVATE - the directory is added to this target’s include directories
* INTERFACE - the directory is added to the include directories for any targets that link this library.
* PUBLIC - As above, it is included in this library and also any targets that link this library.

Tip
>For public headers it is often a good idea to have your include folder be "namespaced" with sub-directories.
>The directory passed to target_include_directories will be the root of your include directory tree and your C++ files should include the path from there to your header.
>For this example you can see that we do it as follows:
> ```#include "static/Hello.h"```
>Using this method means that there is less chance of header filename clashes when you use multiple libraries in your project.

## Linking a Library

When creating an executable that will use your library you must tell the compiler about the library. 
This can be done using the target_link_libraries() function.
```
add_executable(hello_binary
    src/main.cpp
)

target_link_libraries( hello_binary
    PRIVATE
        hello_library
)
```
This tells CMake to link the hello_library against the hello_binary executable during link time. 
It will also propagate any include directories with PUBLIC or INTERFACE scope from the linked library target.

An example of this being called by the compiler is
```
/usr/bin/c++ CMakeFiles/hello_binary.dir/src/main.cpp.o -o hello_binary -rdynamic libhello_library.a
```
## Building the Example;

```
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
-- Build files have been written to: E:/workspace_personal/cmake_tutorials/03-static-library/build


make
λ mingw32-make.exe
Scanning dependencies of target hello_library
[ 25%] Building CXX object CMakeFiles/hello_library.dir/src/Hello.cpp.obj
[ 50%] Linking CXX static library libhello_library.a
[ 50%] Built target hello_library
Scanning dependencies of target hello_binary
[ 75%] Building CXX object CMakeFiles/hello_binary.dir/src/main.cpp.obj
[100%] Linking CXX executable hello_binary.exe
[100%] Built target hello_binary


λ .\hello_binary.exe
Hello Headers!
```