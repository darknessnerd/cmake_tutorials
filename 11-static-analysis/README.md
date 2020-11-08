# Introduction

This example shows how to call the CppCheck tool to do static analysis. This shows how to make an analysis target for each project in your repository.

It includes code to:

* Find the cppcheck binary
* Add cppcheck with a target for each sub-projects
* Generate an overall make analysis target to do static analysis on all sub-projects.

The files included in this example are:


```
λ tree /f
C:.
│   .gitignore
│   CMakeLists.txt
│   main.cpp
│   README.md
│
├───build
├───cmake
│   │   analysis.cmake
│   │
│   └───modules
│           FindCppCheck.cmake
│
└───main
        .gitignore
        CMakeLists.txt
        main.cpp
        README.md
```
* CMakeLists.txt - Top level CMakeLists.txt
* cmake/analysis.cmake - Includes functions to add analysis targets
* cmake/modules/FindCppCheck.cmake - A custom package module to find CppCheck
* main/CMakeLists.txt - CMake commands for main project
* main/main.cpp - source for a subproject that includes errors

# Requirements

To run this example you must have the CppCheck utility installed.
On Ubuntu you can install it as:

```
$ sudo apt-get install cppcheck
```

On Windows you can download and install it from the [installer](http://cppcheck.sourceforge.net/#download).

# Concepts

## Adding Custom Package Modules

Custom modules can be used to find programs, libraries and header files to include in your program.

### Adding a custom module

The cmake/modules/FindCppCheck.cmake file contains the code to initialise a custom package module.

The following is a breakdown of the file:
```
find_program(CPPCHECK_BIN NAMES cppcheck)
```
Search the path for the cppcheck binary. Once found store the result in the CPPCHECK_BIN variable

```
set (CPPCHECK_THREADS "-j 4" CACHE STRING "The -j argument to have cppcheck use multiple threads / cores")
set (CPPCHECK_ARG "${CPPCHECK_THREADS}" CACHE STRING "The arguments to pass to cppcheck. If set will overwrite CPPCHECK_THREADS")
```

Set some custom arguments that can be later passed to cppcheck.

```
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
    CPPCHECK
    DEFAULT_MSG
    CPPCHECK_BIN
    CPPCHECK_THREADS
    CPPCHECK_ARG)

mark_as_advanced(
    CPPCHECK_BIN
    CPPCHECK_THREADS
    CPPCHECK_ARG)
```

Export the variables so that they can be seen from ccmake / cmake-gui and set in the cache. By default these will not be visible unless the view advanced flag is set.

### Setting path to custom modules

The default path that CMake will search for modules is /usr/share/cmake/Modules. To include custom modules you must tell CMake where to search for them. This can be done using the variable ${CMAKE_MODULE_PATH} which contains the paths that CMake will search for modules.

```
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules
                      ${CMAKE_MODULE_PATH})
```

To then add the package module to your CMakeLists.txt you can call
```
find_package(CPPCHECK)
```

## Parent Scope Variables

The scope of variables when they are declared / changed is typically in the function of file the are called. To make a change to a variable which is the caller of your scope, you should call it as follows:
```
set(ALL_ANALYSIS_TARGETS "${ALL_ANALYSIS_TARGETS}" PARENT_SCOPE)
```

## add_analysis macro

The add_analysis() macro in cmake/analysis.cmake is the core idea for this example. If cppcheck is available then a list of arguments are compiled and added to a custom command that calls cppcheck on the sources. These are then added to a custom target.

A breakdown of this macro is below:

```
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
    LIST(APPEND cppcheck_includes "-I${dir}")
endforeach()
```

Find the include files from and calls to include_directories() in the same project.

```
LIST(APPEND ALL_ANALYSIS_TARGETS "${_target}_analysis")
set(ALL_ANALYSIS_TARGETS "${ALL_ANALYSIS_TARGETS}" PARENT_SCOPE)
```

Export the target name into a variable that can later be used to add a global make analysis target.

```
if (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VESION} GREATER 2.7)
    separate_arguments(tmp_args UNIX_COMMAND ${CPPCHECK_ARG})
else ()
    # cmake 2.6 has different arguments
    string(REPLACE " " ";" tmp_args ${CPPCHECK_ARG})
endif ()
```

Change the CPPCHECK_ARG so that the can be added to command correctly in the custom command.

```
add_custom_target(${_target}_analysis)
set_target_properties(${_target}_analysis PROPERTIES EXCLUDE_FROM_ALL TRUE)
```

Add a custom target with a name you have passed in followed by _analysis. Do not include this in the all target.
```
add_custom_command(TARGET ${_target}_analysis PRE_BUILD
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
            COMMAND ${CPPCHECK_BIN} ${tmp_args} ${cppcheck_includes} ${${_sources}}
            DEPENDS ${${_sources}}
            COMMENT "Running cppcheck: ${_target}"
            VERBATIM)
```
Add a custom command which is called from the custom target added above. This will call cppcheck with any includes, arguments and sources that you have provided. The sources that are analysed come from a _sources variable. This should be the name of the variable which holds your list of source files.

To call the add_analysis() marco add the following to your projects CMakeLists.txt file:
```
include(${CMAKE_SOURCE_DIR}/cmake/analysis.cmake)
add_analysis(${PROJECT_NAME} SOURCES)
```

## Creating a target to call other targets

In the top level CMakeLists.txt a custom target is created, which will call all other analysis targets. This allows you to call make analysis and scan all sub projects.

To achieve this 2 things should be added to the top level CMakeLists.txt

First add an empty variable ALL_ANALYSIS_TARGETS before calling your add_subdirectories() function.
```
set (ALL_ANALYSIS_TARGETS)
```

Second add the following after your add_subdirectories() call.

```
if( CPPCHECK_FOUND )
    add_custom_target(analysis)
    ADD_DEPENDENCIES(analysis ${ALL_ANALYSIS_TARGETS})
    set_target_properties(analysis PROPERTIES EXCLUDE_FROM_ALL TRUE)
    message("analysis analysis targets are ${ALL_ANALYSIS_TARGETS}")
endif()
```

This adds the "make analysis" target which calls all the sub-targets.


## Building the example

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
-- Found CPPCHECK: C:/Program Files/Cppcheck/cppcheck.exe
adding cppcheck analysys target for HelloWorld
analysis analysis targets are HelloWorld_analysis
-- Configuring done
-- Generating done
-- Build files have been written to: C:/Users/crini/Documents/workspace/cmake_tutorials/11-static-analysis/build

λ mingw32-make.exe  analysis
Scanning dependencies of target HelloWorld_analysis
Running cppcheck: HelloWorld
Checking main.cpp ...
main.cpp:8:7: error: Array 'tmp[10]' accessed at index 11, which is out of bounds. [arrayIndexOutOfBounds]
   tmp[11] = 's';
      ^
Built target HelloWorld_analysis
Scanning dependencies of target analysis
Built target analysis
```

 The main.cpp includes an out-of-bounds error. This is show in the log.

## Include Directories
In the add_analysis macro in analysis.cmake we extract the INCLUDE_DIRECTORIES from the target and add them to the call to cppcheck.
```
    get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
        foreach(dir ${dirs})
            LIST(APPEND cppcheck_includes "-I${dir}")
        endforeach()
```
This works for basic examples but if you use some CMake features such as generator expressions this will not add the include directory.
