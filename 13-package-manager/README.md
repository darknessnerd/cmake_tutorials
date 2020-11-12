# Introduction


For C++ and CMake there is currently no universally accepted way of managing and packaging dependencies. 
However, in recent years there have been some new and interesting package management systems made available. 
While these are separate systems to CMake, most of them have are designed to integrate directly into a CMake based build system.

* Using System Provided Package Manager: Using your system provided packages is one of the oldest and most common 
form of package management solutions. For this, you use your systems package installer (e.g. apt, yum) to install 
libraries and headers into common locations. CMake can then use the find_package() function to search for 
these and make them available to your program.

* Vendoring Code: Vendoring code means to include the third party code inside your repository and build it as part of your project. 
It is a way to ensure that all files required to build your project are part of the development environment. (3rd_party or vendor directory)

* External Project: CMake supports downloading and building an external project using the External Project commands. 
  By adding ExternalProject_Add to your code you can have CMake automatically download a source file from either HTTP or a source control system (e.g. git). 
  Once configured an external project will generate a custom target which can be used to control the download, update, build, test, and install phases of the external project.

* Vcpkg: 
Vcpkg helps you manage C and C++ libraries on Windows, Linux and MacOS. This tool and ecosystem are constantly evolving, and we always appreciate contributions!


# Concepts

## Install 

### Windows

Prerequisites:

* Windows 7 or newer
* Git
* Visual Studio [download link](https://visualstudio.microsoft.com/it/)

First, download and bootstrap vcpkg itself; it can be installed anywhere, but generally we recommend using vcpkg as a submodule for 
CMake projects, and installing it globally for Visual Studio projects. ( make sure to install the english language package)
> add this to the PATH env C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.28.29333\bin\Hostx64\x64
> for the bumpbin
In order to copy the dll in the build path 
We recommend somewhere like C:\src\vcpkg or C:\dev\vcpkg, since otherwise you may run into path issues for some port build systems.

```
> git clone https://github.com/microsoft/vcpkg
> .\vcpkg\bootstrap-vcpkg.bat
```

To install the libraries for your project, run:

```
> .\vcpkg\vcpkg install [packages to install]
```

You can also search for the libraries you need with the search subcommand:

```
> .\vcpkg\vcpkg search [search term]
```


### Unix

Prerequisites for Linux:

* Git
* g++ >= 6

First, download and bootstrap vcpkg itself; it can be installed anywhere, but generally we recommend using vcpkg as a submodule for CMake projects.

```
$ sudo apt-get update
$ sudo apt-get install build-essential tar curl zip unzip
$ git clone https://github.com/microsoft/vcpkg
$ ./vcpkg/bootstrap-vcpkg.sh
```


## Usage: Install Library

First, we need to know what name SQLite goes by in the ports tree. To do that, we'll run the search command and inspect the output:

```
C:\dev\vcpkg (master -> origin)
λ .\vcpkg search sqlite
dlib[sqlite3]                         sqlite3 support for dlib
libodb-sqlite        2.4.0#7          Sqlite support for the ODB ORM library
libspatialite        4.3.0a#5         SpatiaLite is an open source library intended to extend the SQLite core to sup...
oatpp-sqlite         1.2.0#1          Oat++ SQLite adapter for Oat++ ORM.
soci[sqlite3]                         Build sqlite3 backend
sqlcipher            4.4.0#1          SQLCipher extends the SQLite database library to add security enhancements tha...
sqlcipher[geopoly]                    enable geopoly functionality for sqlite3
sqlcipher[json1]                      enable JSON functionality for sqlite3
sqlcipher[tool]                       sqlite3 executable
sqlite-modern-cpp    3.2-936cd0c8     The C++14 wrapper around sqlite library
sqlite-orm           1.5#2            SQLite ORM light header only library for modern C++
sqlite-orm[example]                   Build examples
sqlite-orm[test]                      Build sqlite_orm unit tests
sqlite3              3.33.0           SQLite is a software library that implements a self-contained, serverless, zer...
sqlite3[geopoly]                      enable geopoly functionality for sqlite3
sqlite3[json1]                        enable JSON functionality for sqlite3
sqlite3[tool]                         sqlite3 executable
sqlitecpp            3.1.1#1          SQLiteC++ (SQLiteCpp) is a smart and easy to use C++ SQLite3 wrapper.
sqlitecpp[sqlcipher]                  Use the sqlcipher port
sqlitecpp[sqlite]                     Use the (unofficial) sqlite3 port of vcpkg
sqlpp11-connector... 0.30             A C++ wrapper for sqlite3 meant to be used in combination with sqlpp11.
wt[sqlite3]                           Wt::Dbo Sqlite 3 backend

If your library is not listed, please open an issue at and/or consider making a pull request:
    https://github.com/Microsoft/vcpkg/issues
```

Looking at the list, we can see that the port is named "sqlite3". You can also run the search command without arguments to see the full list of packages.

Installing is then as simple as using the install command.

```
C:\dev\vcpkg (master -> origin)
λ .\vcpkg.exe --triplet x64-mingw-dynamic install sqlite3
...
...
Stored binary cache: C:\Users\crini\AppData\Local\vcpkg\archives\6f\6f847a2b9f4b56601b0dc046acdd9e6ddb0f30f8.zip
Building package sqlite3[core]:x86-windows... done
Installing package sqlite3[core]:x86-windows...
Installing package sqlite3[core]:x86-windows... done
Elapsed time for package sqlite3:x86-windows: 28.36 s

Total elapsed time: 1.662 min

The package sqlite3:x86-windows provides CMake targets:

    find_package(unofficial-sqlite3 CONFIG REQUIRED)
    target_link_libraries(main PRIVATE unofficial::sqlite3::sqlite3)
```
We can check that sqlite3 was successfully installed for x86 Windows desktop by running the list command.
```
C:\dev\vcpkg (master -> origin)
λ .\vcpkg list
sqlite3:x86-windows                                3.33.0           SQLite is a software library that implements a s..
```

To install for other architectures and platforms such as Universal Windows Platform or x64 Desktop, you can suffix the package name with :<target>.

## Usage: use sqlite

CMake (Toolchain File)
The best way to use installed libraries with cmake is via the toolchain file scripts\buildsystems\vcpkg.cmake.
To use this file, you simply need to add it onto your CMake command line as:

```
-DCMAKE_TOOLCHAIN_FILE=C:\dev\vcpkg\scripts\buildsystems\vcpkg.cmake
-DVCPKG_TARGET_TRIPLET="x64-mingw-dynamic"
```

Now let's make a simple CMake project with a main file.

```
# CMakeLists.txt
cmake_minimum_required(VERSION 3.5)
# set the project name
project(HelloWorld)


find_package(unofficial-sqlite3 CONFIG REQUIRED)


# add the executable
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::sqlite3::sqlite3)
```

```
#include <iostream>
#include <sqlite3.h>

int main(int argc, char *argv[])
{
   std::cout << sqlite3_libversion() << std::endl;
   return 0;
}
```

## Building example

```
mkdir build
cd build
λ cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE="C:\dev\vcpkg\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-mingw-dynamic" ..
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
-- Build files have been written to: C:/Users/crini/Documents/workspace/cmake_tutorials/13-package-manager/build

λ mingw32-make.exe
Scanning dependencies of target HelloWorld
[ 50%] Building CXX object CMakeFiles/HelloWorld.dir/main.cpp.obj
[100%] Linking CXX executable HelloWorld.exe
[100%] Built target HelloWorld


λ .\HelloWorld.exe
3.33.0


```
