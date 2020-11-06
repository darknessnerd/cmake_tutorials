# Introduction

Shows a hello world example which first creates and links a shared library.
This also shows how to create an alias target
The files in this tutorial are below:

$ tree
.
├── CMakeLists.txt
├── include
│   └── shared
│       └── Hello.h
└── src
    ├── Hello.cpp
    └── main.cpp
    
*CMakeLists.txt - Contains the CMake commands you wish to run
*include/shared/Hello.h - The header file to include
*src/Hello.cpp - A source file to compile
*src/main.cpp - The source file with main

# Concepts
## Adding a Shared Library

As with the previous example on static libraries, 
the add_library() function is also used to create a shared library 
from some source files. This is called as follows:

```
add_library(hello_library SHARED
    src/Hello.cpp
)
```

This will be used to create a shared library with the name libhello_library.so 
with the sources passed to the add_library() function.

## Alias Target
As the name suggests an alias target is an alternative name for a target that can
be used instead of the real target name in read-only contexts.
```
add_library(hello::library ALIAS hello_library)
```

As shown below, this allows you to reference the target using the alias name when
linking it against other targets.

## Linking a Shared Library

Linking a shared library is the same as linking a static library. 
When creating your executable use the the target_link_library() 
function to point to your library

```
add_executable(hello_binary
    src/main.cpp
)

target_link_libraries(hello_binary
    PRIVATE
        hello::library
)
```

This tells CMake to link the hello_library against the hello_binary
executable using the alias target name.

An example of this being called by the linker is
```
/usr/bin/c++ CMakeFiles/hello_binary.dir/src/main.cpp.o -o hello_binary -rdynamic libhello_library.so -Wl,-rpath,/home/matrim/workspace/cmake-examples/01-basic/D-shared-library/build
```

## Building the Example

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
-- Build files have been written to: E:/workspace_personal/cmake_tutorials/04-shared-library/build


λ mingw32-make.exe
Scanning dependencies of target hello_library
[ 25%] Building CXX object CMakeFiles/hello_library.dir/src/Hello.cpp.obj
[ 50%] Linking CXX shared library libhello_library.dll
[ 50%] Built target hello_library
Scanning dependencies of target hello_binary
[ 75%] Building CXX object CMakeFiles/hello_binary.dir/src/main.cpp.obj
[100%] Linking CXX executable hello_binary.exe
[100%] Built target hello_binary


λ .\hello_binary.exe
Hello Headers!

```