# Introduction


CMake supports setting compile flags in a number of different ways:

* using target_compile_definitions() function
* using the CMAKE_C_FLAGS and CMAKE_CXX_FLAGS variables.

The files in this tutorial are below:
```
$ tree
.
├── CMakeLists.txt
├── main.cpp
```

* CMakeLists.txt - Contains the CMake commands you wish to run
* main.cpp - The source file with main

# Concepts

## Set Per-Target C++ Flags

The recommended way to set C++ flags in modern CMake is to use per-target flags which can be populated to other targets through the [target_compile_definitions()](https://cmake.org/cmake/help/v3.0/command/target_compile_definitions.html?highlight=target_compile_definitions). This will populate the [INTERFACE_COMPILE_DEFINITIONS](https://cmake.org/cmake/help/v3.0/prop_tgt/INTERFACE_COMPILE_DEFINITIONS.html#prop_tgt:INTERFACE_COMPILE_DEFINITIONS) for the library and push the definition to the linked target depending on the scope.

```
target_compile_definitions(hello_flags_bin 
    PRIVATE EX3
)
```
This will cause the compiler to add the definition -DEX3 when compiling the target.

In the target was a library, and the scope PUBLIC or INTERFACE has been chosen the definition would also be included in any executables that link this target.

For compiler options you can also use the [target_compile_options()](https://cmake.org/cmake/help/v3.0/command/target_compile_options.html)

## Set Default C++ Flags


The default CMAKE_CXX_FLAGS is either empty or contains the appropriate flags for the build type.
To set additional default compile flags you can add the following to your top level CMakeLists.txt


```
#Extends the default CMAKE flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)
```

```
# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
```

Similarly to CMAKE_CXX_FLAGS other options include:

* Setting C compiler flags using CMAKE_C_FLAGS

* Setting linker flags using CMAKE_LINKER_FLAGS.

Note
> The values CACHE STRING "Set C++ Compiler Flags" FORCE from the above command are used to force this variable to be set in the CMakeCache.txt file. For more details, see [here](https://cmake.org/cmake/help/v3.0/command/set.html)

## Building the Example
