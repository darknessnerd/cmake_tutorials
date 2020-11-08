# Introduction

This example shows how to generate a make install target to install files
and binaries on your system. This is based on the previous shared library example.

The files in this tutorial are below:

```
$ tree
.
├── cmake-examples.conf
├── CMakeLists.txt
├── include
│   └── installing
│       └── Hello.h
├── README.adoc
└── src
    ├── Hello.cpp
    └── main.cpp
```

* CMakeLists.txt - Contains the CMake commands you wish to run
* cmake-examples.conf - An example configuration file
* include/installing/Hello.h - The header file to include
* src/Hello.cpp - A source file to compile
* src/main.cpp - The source file with main

# Concepts

## Installing

CMake offers the ability to add a make install target to allow a user to install binaries, 
libraries and other files. The base install location is controlled by the variable 
CMAKE_INSTALL_PREFIX which can be set using ccmake or by calling cmake with 

```
cmake .. -DCMAKE_INSTALL_PREFIX=/install/location
```

The files that are installed are controlled by the install() function.

```
install (TARGETS cmake_examples_inst_bin DESTINATION bin)
```
Install the binary generated from 
the target cmake_examples_inst_bin target to the destination ${CMAKE_INSTALL_PREFIX}/bin

```
install (TARGETS cmake_examples_inst
    LIBRARY DESTINATION lib)
```
Install the shared library generated from
the target cmake_examples_inst target to the destination ${CMAKE_INSTALL_PREFIX}/lib

Note
> This may not work on windows. On platforms that have DLL targets you
> may need to add the following

```
install (TARGETS cmake_examples_inst
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
```

```
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION include)
```
Install the header files for developing against 
the cmake_examples_inst library into the ${CMAKE_INSTALL_PREFIX}/include directory.

```
install (FILES cmake-examples.conf
    DESTINATION etc)
```
Install a configuration file to the destination ${CMAKE_INSTALL_PREFIX}/etc

After make install has been run, CMake generates an install_manifest.txt 
file which includes details on all installed files.

Note
> If you run the make install command as root, the install_manifest.txt
> file will be owned by root.

## Building the Example

```
λ mkdir build
λ cd build/
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
-- Build files have been written to: E:/workspace_personal/cmake_tutorials/05-installing/build

λ mingw32-make.exe
Scanning dependencies of target cmake_examples_inst
[ 25%] Building CXX object CMakeFiles/cmake_examples_inst.dir/src/Hello.cpp.obj
[ 50%] Linking CXX shared library libcmake_examples_inst.dll
[ 50%] Built target cmake_examples_inst
Scanning dependencies of target cmake_examples_inst_bin
[ 75%] Building CXX object CMakeFiles/cmake_examples_inst_bin.dir/src/main.cpp.obj
[100%] Linking CXX executable cmake_examples_inst_bin.exe
[100%] Built target cmake_examples_inst_bin

λ mingw32-make.exe install
[ 50%] Built target cmake_examples_inst
[100%] Built target cmake_examples_inst_bin
Install the project...
-- Install configuration: ""
-- Installing: C:/Program Files (x86)/cmake_examples_install/bin/cmake_examples_inst_bin.exe
-- Installing: C:/Program Files (x86)/cmake_examples_install/lib/libcmake_examples_inst.dll.a
-- Installing: C:/Program Files (x86)/cmake_examples_install/bin/libcmake_examples_inst.dll
-- Installing: C:/Program Files (x86)/cmake_examples_install/include
-- Installing: C:/Program Files (x86)/cmake_examples_install/include/installing
-- Installing: C:/Program Files (x86)/cmake_examples_install/include/installing/Hello.h
-- Installing: C:/Program Files (x86)/cmake_examples_install/etc/cmake-examples.conf

λ cat install_manifest.txt
C:/Program Files (x86)/cmake_examples_install/bin/cmake_examples_inst_bin.exe
C:/Program Files (x86)/cmake_examples_install/lib/libcmake_examples_inst.dll.a
C:/Program Files (x86)/cmake_examples_install/bin/libcmake_examples_inst.dll
C:/Program Files (x86)/cmake_examples_install/include/installing/Hello.h
C:/Program Files (x86)/cmake_examples_install/etc/cmake-examples.conf

λ "C:/Program Files (x86)/cmake_examples_install/bin/cmake_examples_inst_bin.exe"
Hello Headers!
```

## Extra Notes
Overriding the default install location
As mentioned the default install location is set from the CMAKE_INSTALL_PERFIX, 
which defaults to /usr/local/
If you want to change this default location for all users you can add the following 
code to your top level CMakeLists.txt before adding any binaries or libraries.
```
if( CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT )
  message(STATUS "Setting default CMAKE_INSTALL_PREFIX path to ${CMAKE_BINARY_DIR}/install")
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING "The path to use for make install" FORCE)
endif()
```
This example sets the default install location to under your build directory.

### DESTDIR
If you wish to stage your install to confirm that all files are included the make install target supports the DESTDIR argument.
```
make install DESTDIR=/tmp/stage
```

This will create the install path ${DESTDIR}/${CMAKE_INSTALL_PREFIX} for all your installation files. In this example, 
it would install all files under the path /tmp/stage/usr/local

```
$ tree /tmp/stage
/tmp/stage
└── usr
    └── local
        ├── bin
        │   └── cmake_examples_inst_bin
        ├── etc
        │   └── cmake-examples.conf
        └── lib
            └── libcmake_examples_inst.so
```

### Uninstall

By default CMake does not add a make uninstall target. For details on how to generate 
an uninstall target see this [FAQ](https://cmake.org/Wiki/CMake_FAQ#Can_I_do_.22make_uninstall.22_with_CMake.3F)

For an easy way to remove the files from this example, you can use:
```
sudo xargs rm < install_manifest.txt
```
