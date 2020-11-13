# Introduction


[Conan](https://conan.io/) is an open source, decentralized, and multi-platform package manager that can be used to create and share native
libraries and binaries. It supports multiple build systems (CMake, Visual Studio, Makefiles) and OSes 
(Linux, Windows, and Mac).

Conan servers can be installed privately or you can use public servers and packages made available by Jfrog bintray.

Full documentation for conan can be found from [here](https://docs.conan.io/en/latest/)

# Concepts

## Install 

Conan is a python application and can be installed using pip.

Create a virtual env named conan
```
python -m venv C:\envs\conan
```

activate the conan env and install conan

```
C:\envs\conan\Scripts\activate.bat
pip install conan
```

Alternatively, native packages are available for most operating systems. Full details are available [here](https://docs.conan.io/en/latest/installation.html).



## Conan Profile

In conan profiles control information such as the compiler and environments that are available on your system.

To create a new default profile run

```
conan profile new default --detect
```

or configre manually, need to be sure in the PATH for example: there are mingw and cmake

```
[build_requires]
[settings]
    os=Windows
    os_build=Windows
    arch=x86_64
    arch_build=x86_64
    compiler=gcc
    compiler.version=8.1
    compiler.libcxx=libstdc++11
    build_type=Debug
[options]
[env]
```

## Finding Packages
Remote repositories can be searched for conan packages. By default the conan-center remote is configured. 
This is located in bintray.

### Searching for Packages
You can search for packages using the conan search command. For example, to search for a package such
as fmtlib you can run:

```
(conan) λ conan search sqlite3 --remote=conan-center
Existing package recipes:

sqlite3/3.14.1@bincrafters/stable
sqlite3/3.20.1@bincrafters/stable
sqlite3/3.21.0@bincrafters/stable
sqlite3/3.25.3@bincrafters/stable
sqlite3/3.26.0@bincrafters/stable
sqlite3/3.27.1@bincrafters/stable
sqlite3/3.27.2@bincrafters/stable
sqlite3/3.28.0@bincrafters/stable
sqlite3/3.29.0
sqlite3/3.29.0@bincrafters/stable
sqlite3/3.30.1
sqlite3/3.31.0
sqlite3/3.31.1
sqlite3/3.32.1
sqlite3/3.32.2
sqlite3/3.32.3
sqlite3/3.33.0
```

### Inspecting Packages
You can then inspect a package using the conan inspect command. To inspect one one of the fmt packages
from the search command above you can run:

```
conan inspect sqlite3/3.33.0 --remote=conan-center
```


## Example

This example shows how to support this using conan in an CMake build.

The files in this tutorial are below:

```
.
├── CMakeLists.txt
├── conanfile.txt
├── main.cpp
└── README.md
```

* CMakeLists.txt - Contains the CMake commands to run
* conanfile.txt - Contains the conan dependencies and options
* main.cpp - Source file of the application.


### Libraries Targets

Create a conanfile.txt that contains the required libraries

```
[requires]
sqlite3/3.29.0@bincrafters/stable
[generators]
cmake
```

### Conan Imported Targets

To configure conan to use imported targets add the argument TARGETS to the conan_basic_setup function.
 This will cause conan to create a CONAN_PKG::pkg_name target that can be imported as a library.
An example of this using the sqlite3 library is below:


```
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
```

### Building the Example

In this example we are using Mingw, and the binary for mingw is not in the repository, and it is possible to build 
from sources with '--build=sqlite3'

```
conan install .. --build=sqlite3

cmake -G "MinGW Makefiles" ..

mingw32-make.exe

(conan) λ .\bin\HelloWorld.exe
3.29.0
 
```