# Introduction

Nearly all non-trivial projects will have a requirement for including third party libraries, headers, or programs. CMake has support for finding the path to these tools using the find_package() function. This will search for CMake modules in the format "FindXXX.cmake" from the list of folders in CMAKE_MODULE_PATH. On linux the default search path will include /usr/share/cmake/Modules.
On my system this includes support for approximately 142 common third party libraries.

The files in this tutorial are below:

```
$ tree
.
├── CMakeLists.txt
├── main.cpp
```

* CMakeLists.txt - Contains the CMake commands you wish to run
* main.cpp - The source file with main

# Requirements

This example requires the curl libraries to be installed in a default system location.

# Concepts
## Finding a Package

As mentioned above the find_package() function will search for CMake modules in the formant "FindXXX.cmake" from the list of folders in CMAKE_MODULE_PATH. The exact format of the arguments to find_package will depend on the module you are looking for. This is typically documented at the top of the FindXXX.cmake file.

A basic example of finding boost is below:

```
find_package(CURL 7.73.0 REQUIRED)
```
The arguments are:

* Curl - Name of the library. This is part of used to find the module file FindCurl.cmake

* 7.73.0 - The minimum version of curl to find

* REQUIRED - Tells the module that this is required and to fail it  cannot be found

## Exported Variables
After a package is found it will often export variables which can inform the user where to find the library, header, or executable files. Similar to the XXX_FOUND variable, these are package specific and are typically documented at the top of the [FindXXX.cmake](https://cmake.org/cmake/help/latest/module/FindCURL.html?highlight=findcurl) file.

The variables exported in this example include:

CURL_INCLUDE_DIRS - The path to the curl header files.

In some cases you can also check these variables by examining the cache using ccmake or cmake-gui.

## Alias / Imported targets
Most modern CMake libraries export ALIAS targets in their module files. The benefit of imported targets are that they can also populate include directories and linked libraries.

For example, starting from v3.5+ of CMake, the Curl module supports this. Similar to using your own ALIAS target for libraires, an ALIAS in a module can make referencing found targets easier.

In the case of Boost, all targets are exported using the CURL::libcurl identifier and then the name of the subsystem. For example
To link against an imported target you can use the following:
```
  target_link_libraries( third_party_include
      PRIVATE
          CURL::libcurl
  )
  ```
  ## Non-alias targets
  While most modern libraries use imported targets, not all modules have been updated. In the case where a library hasn’t been updated you will often find the following variables available:

  xxx_INCLUDE_DIRS - A variable pointing to the include directory for the library.

  xxx_LIBRARY - A variable pointing to the library path.

  These can then be added to your target_include_directories and target_link_libraries as:
  ```
  # Include the boost headers
  target_include_directories( third_party_include
      PRIVATE ${CURL_INCLUDE_DIRS}
  )
  ```
    ```
  # link against the boost libraries
  target_link_libraries( third_party_include
      PRIVATE
      ${CURL_LIBRARIES}
  )
  ```
## Building the Example
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
-- Found CURL: C:/Program Files/CodeBlocks/MinGW/lib/libcurl.dll.a (found suitable version "7.73.0", minimum required is "7.73.0")
C:/Program Files/CodeBlocks/MinGW/lib/libcurl.dll.a
C:/Program Files/CodeBlocks/MinGW/include
curl found
-- Configuring done
-- Generating done
-- Build files have been written to: C:/Users/crini/Documents/workspace/cmake_tutorials/09-hello-world/build

λ mingw32-make.exe  VERBOSE=1
"C:\Program Files\CMake\bin\cmake.exe" -SC:\Users\crini\Documents\workspace\cmake_tutorials\09-hello-world -BC:\Users\crini\Documents\workspace\cmake_tutorials\09-hello-world\build --check-build-system CMakeFiles\Makefile.cmake 0
"C:\Program Files\CMake\bin\cmake.exe" -E cmake_progress_start C:\Users\crini\Documents\workspace\cmake_tutorials\09-hello-world\build\CMakeFiles C:\Users\crini\Documents\workspace\cmake_tutorials\09-hello-world\build\\CMakeFiles\progress.marks
mingw32-make.exe  -f CMakeFiles\Makefile2 all
mingw32-make.exe[1]: Entering directory 'C:/Users/crini/Documents/workspace/cmake_tutorials/09-hello-world/build'
mingw32-make.exe  -f CMakeFiles\third_party_include.dir\build.make CMakeFiles/third_party_include.dir/depend
mingw32-make.exe[2]: Entering directory 'C:/Users/crini/Documents/workspace/cmake_tutorials/09-hello-world/build'
"C:\Program Files\CMake\bin\cmake.exe" -E cmake_depends "MinGW Makefiles" C:\Users\crini\Documents\workspace\cmake_tutorials\09-hello-world C:\Users\crini\Documents\workspace\cmake_tutorials\09-hello-world C:\Users\crini\Documents\workspace\cmake_tutorials\09-hello-world\build C:\Users\crini\Documents\workspace\cmake_tutorials\09-hello-world\build C:\Users\crini\Documents\workspace\cmake_tutorials\09-hello-world\build\CMakeFiles\third_party_include.dir\DependInfo.cmake --color=
Dependee "C:\Users\crini\Documents\workspace\cmake_tutorials\09-hello-world\build\CMakeFiles\third_party_include.dir\DependInfo.cmake" is newer than depender "C:/Users/crini/Documents/workspace/cmake_tutorials/09-hello-world/build/CMakeFiles/third_party_include.dir/depend.internal".
Dependee "C:/Users/crini/Documents/workspace/cmake_tutorials/09-hello-world/build/CMakeFiles/CMakeDirectoryInformation.cmake" is newer than depender "C:/Users/crini/Documents/workspace/cmake_tutorials/09-hello-world/build/CMakeFiles/third_party_include.dir/depend.internal".
Scanning dependencies of target third_party_include
mingw32-make.exe[2]: Leaving directory 'C:/Users/crini/Documents/workspace/cmake_tutorials/09-hello-world/build'
mingw32-make.exe  -f CMakeFiles\third_party_include.dir\build.make CMakeFiles/third_party_include.dir/build
mingw32-make.exe[2]: Entering directory 'C:/Users/crini/Documents/workspace/cmake_tutorials/09-hello-world/build'
[ 50%] Building CXX object CMakeFiles/third_party_include.dir/main.cpp.obj
C:\PROGRA~1\CODEBL~1\MinGW\bin\G__~1.EXE  @CMakeFiles/third_party_include.dir/includes_CXX.rsp  -o CMakeFiles\third_party_include.dir\main.cpp.obj -c C:\Users\crini\Documents\workspace\cmake_tutorials\09-hello-world\main.cpp
[100%] Linking CXX executable third_party_include.exe
"C:\Program Files\CMake\bin\cmake.exe" -E cmake_link_script CMakeFiles\third_party_include.dir\link.txt --verbose=1
"C:\Program Files\CMake\bin\cmake.exe" -E rm -f CMakeFiles\third_party_include.dir/objects.a
C:\PROGRA~1\CODEBL~1\MinGW\bin\ar.exe cr CMakeFiles\third_party_include.dir/objects.a @CMakeFiles\third_party_include.dir\objects1.rsp
C:\PROGRA~1\CODEBL~1\MinGW\bin\G__~1.EXE -Wl,--whole-archive CMakeFiles\third_party_include.dir/objects.a -Wl,--no-whole-archive -o third_party_include.exe -Wl,--out-implib,libthird_party_include.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles\third_party_include.dir\linklibs.rsp
mingw32-make.exe[2]: Leaving directory 'C:/Users/crini/Documents/workspace/cmake_tutorials/09-hello-world/build'
[100%] Built target third_party_include
mingw32-make.exe[1]: Leaving directory 'C:/Users/crini/Documents/workspace/cmake_tutorials/09-hello-world/build'
"C:\Program Files\CMake\bin\cmake.exe" -E cmake_progress_start C:\Users\crini\Documents\workspace\cmake_tutorials\09-hello-world\build\CMakeFiles 0

λ .\third_party_include.exe
Hello Third Party Include!
<!doctype html><html....


  ```
