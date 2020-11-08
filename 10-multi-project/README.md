# Introduction

Many large projects are made up of different libraries and binaries.
These can be organised into multiple folders and sub-projects to ease development.

This example shows how to setup a CMake project that includes sub-projects. The top level CMakeLists.txt calls the CMakeLists.txt in the sub directories to create the following:

* RandomGenerator - A static library
* helloWorldPrinter - A header only library
* main - An executable

The files included in this example are:

```
λ tree /f
C:.
│   .gitignore
│   CMakeLists.txt
│   main.cpp
│   README.md
│
├───helloWorldPrinter
│   │   CMakeLists.txt
│   │
│   └───include
│       └───helloWorldPrinter
│               HelloWorldPrinter.h
│
├───main
│   │   CMakeLists.txt
│   │   main.cpp
│   │
│   └───src
└───randomGenerator
    │   CMakeLists.txt
    │
    ├───include
    │   └───randomGenerator
    │           RandomGenerator.h
    │
    └───src
            RandomGenerator.cpp
```


* CMakeLists.txt - Top level CMakeLists.txt
* main/CMakeLists.txt - to make the executable
* main/src/main.cpp - source for the executable
* randomGenerator/CMakeLists.txt - to make a static library
* randomGenerator/include/randomGenerator/randomGenerator.h
* randomGenerator/src/randomGenerator.cpp
* helloWorldPrinter/CMakeLists.txt - to setup header only library
* helloWorldPrinter/include/helloWorldPrinter/helloWorldPrinter.h*


# Requirements

This example requires the curl libraries to be installed in a default system location.

# Concepts

## Adding a Sub-Directory

A CMakeLists.txt file can include and call sub-directories which include a CMakeLists.txt files.

```
add_subdirectory(helloWorldPrinter)
add_subdirectory(randomGenerator)
add_subdirectory(main)
```

## Referencing Sub-Project Directories

When a project is created using the project() command, CMake will automatically create a number of variables which can be used to reference details about the project. These variables can then be used by other sub-projects or the main project. For example, to reference the source directory for a different project you can use.

```
${randomGenerator_SOURCE_DIR}
${helloWorldPrinter_SOURCE_DIR}
${main_SOURCE_DIR}
```


The variables created by CMake include:

|Variable|Info|
|--------|----|
|PROJECT_NAME|The name of the project set by the current project().|
|CMAKE_PROJECT_NAME|the name of the first project set by the project() command, i.e. the top level project.|
|PROJECT_SOURCE_DIR|The source director of the current project.|
|PROJECT_BINARY_DIR|The build directory for the current project.|
|name_SOURCE_DIR|The source directory of the project called "name". In this example the source directories created would be sublibrary1_SOURCE_DIR, sublibrary2_SOURCE_DIR, and subbinary_SOURCE_DIR|
|name_BINARY_DIR|The binary directory of the project called "name". In this example the binary directories created would be sublibrary1_BINARY_DIR, sublibrary2_BINARY_DIR, and subbinary_BINARY_DIR|


## Header only Libraries

If you have a library that is created as a header only library, cmake supports the INTERFACE target to allow creating a target without any build output. More details can be found from [here](https://cmake.org/cmake/help/v3.4/command/add_library.html#interface-libraries)

```
add_library(${PROJECT_NAME} INTERFACE)
```

When creating the target you can also include directories for that target using the INTERFACE scope. The INTERFACE scope is use to make target requirements that are used in any Libraries that link this target but not in the compilation of the target itself.

```
target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)
```

## Referencing Libraries from Sub-Projects

If a sub-project creates a library, it can be referenced by other projects by calling the name of the project in the target_link_libraries() command. This means that you don’t have to reference the full path of the new library and it is added as a dependency.

```
target_link_libraries(main
    PUBLIC
        randomGenerator
)
```
Alternatively, you can create an alias target which allows you to reference the target in read only contexts.

To create an alias target run:
```
add_library(helloWorldPrinter)
add_library(sub::helloWorldPrinter ALIAS helloWorldPrinter)
```
To reference the alias, just it as follows:
```
target_link_libraries(main
    sub::helloWorldPrinter
)
```

## Include directories from sub-projects

When adding the libraries from the sub-projects, starting from cmake v3, there is no need to add the projects include directories in the include directories of the binary using them.

This is controlled by the scope in the target_include_directories() command when creating the libraries. In this example because the subbinary executable links the sublibrary1 and sublibrary2 libraries it will automatically include the ${sublibrary1_SOURCE_DIR}/inc and ${sublibrary2_SOURCE_DIR}/inc folders as they are exported with the PUBLIC and INTERFACE scopes of the libraries.


#  Building the example


```
λ cmake -G "MinGW Makefiles" ..
-- The C compiler identification is GNU 8.1.0
-- The CXX compiler identification is GNU 8.1.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/Program Files/CodeBlocks/MinGW/bin/gcc.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: C:/Program Files/CodeBlocks/MinGW/bin/g++.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: C:/Users/crini/Documents/workspace/cmake_tutorials/10-multi-project/build

λ mingw32-make.exe
Scanning dependencies of target randomGenerator
[ 25%] Building CXX object randomGenerator/CMakeFiles/randomGenerator.dir/src/RandomGenerator.cpp.obj
[ 50%] Linking CXX static library librandomGenerator.a
[ 50%] Built target randomGenerator
Scanning dependencies of target main
[ 75%] Building CXX object main/CMakeFiles/main.dir/src/main.cpp.obj
[100%] Linking CXX executable main.exe
[100%] Built target main

λ main\main.exe
581869302
RandomGenerator result:4.17875
RandomGenerator result:4.74602
RandomGenerator result:3.78297
RandomGenerator result:3.54607
Hello world from  HelloWorldPrinter static headers only lib!

```
