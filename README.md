# Introduction

This example shows how to download and build the google test library, create tests and run them.

The files in this tutorial are below:

```
```


# Requirements

An internet connection. This example will download the google test library the first time you run the CMake configure step.
 See the [google test readme](https://github.com/google/googletest/blob/master/googletest/README.md).
 
 
 # Concepts
 
 ## Download and Build Google Test
 
 This will add the CMake files which download and build Google Test. 
 
```
add_subdirectory(3rd_party/google-test)
```

Alternatives to this method include:

* Use something like git submodule to download the source to a folder in your tree and then do add_subdirectory

* Vendor the google test source code within your repository

* Build google test externally and link it using find_package(GTest) - Not recommended by the google test authors anymore

## Enabling testing

To enable testing you must include the following line in your top level CMakeLists.txt

```
enable_testing()
```

This will enable testing for the current folder and all folders below it.

## Adding a testing executable

Create binary(s) which includes all the unit tests that you want to run.

```
add_executable(ReverseTest ReverseTest.cpp src/Reverse.cpp)

target_link_libraries(ReverseTest
    GTest::GTest 
    GTest::Main
)
target_include_directories(ReverseTest
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src/include
)
```
In the above code, a unit test binary is added, which links against the google test 
unit-test-framework using the ALIAS target setup during the [download and build](https://github.com/ttroy50/cmake-examples/blob/master/05-unit-testing/google-test-download/3rd_party/google-test/CMakeLists.txt)
of GTest.

## Add a test

To add a test you call the [add_test()](https://cmake.org/cmake/help/v3.0/command/add_test.html) function. This will create a named test which will run the supplied command.

```
# add the test {test name} and class test 
add_test(reverse_class_test ReverseTest)
```

In this example, we create a test called reverse_class_test which will run the executable created by the ReverseTest executable created from the call to add_executable

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
-- Configuring done
-- Generating done
-- Build files have been written to: C:/Users/crini/Documents/workspace/cmake_tutorials/11-google-test/build/3rd_party/google-test/googletest-download
Scanning dependencies of target googletest
[ 11%] Creating directories for 'googletest'
[ 22%] Performing download step (download, verify and extract) for 'googletest'
-- Downloading...
   dst='C:/Users/crini/Documents/workspace/cmake_tutorials/11-google-test/build/3rd_party/google-test/googletest-download/googletest-prefix/src/release-1.10.0.zip'
   timeout='none'
-- Using src='https://github.com/google/googletest/archive/release-1.10.0.zip'
-- [download 100% complete]
-- Downloading... done
-- extracting...
     src='C:/Users/crini/Documents/workspace/cmake_tutorials/11-google-test/build/3rd_party/google-test/googletest-download/googletest-prefix/src/release-1.10.0.zip'
     dst='C:/Users/crini/Documents/workspace/cmake_tutorials/11-google-test/build/3rd_party/google-test/googletest-src'
-- extracting... [tar xfz]
-- extracting... [analysis]
-- extracting... [rename]
-- extracting... [clean up]
-- extracting... done
[ 33%] No update step for 'googletest'
[ 44%] No patch step for 'googletest'
[ 55%] No configure step for 'googletest'
[ 66%] No build step for 'googletest'
[ 77%] No install step for 'googletest'
[ 88%] No test step for 'googletest'
[100%] Completed 'googletest'
[100%] Built target googletest
-- Could NOT find PythonInterp (missing: PYTHON_EXECUTABLE)
-- Configuring done
-- Generating done
-- Build files have been written to: C:/Users/crini/Documents/workspace/cmake_tutorials/11-google-test/build


λ mingw32-make.exe
Scanning dependencies of target main
[  7%] Building CXX object CMakeFiles/main.dir/src/Reverse.cpp.obj
[ 14%] Building CXX object CMakeFiles/main.dir/src/main.cpp.obj
[ 21%] Linking CXX executable main.exe
[ 21%] Built target main
Scanning dependencies of target gtest
[ 28%] Building CXX object 3rd_party/google-test/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.obj
[ 35%] Linking CXX static library ..\..\..\..\lib\libgtest.a
[ 35%] Built target gtest
Scanning dependencies of target gtest_main
[ 42%] Building CXX object 3rd_party/google-test/googletest-build/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.obj
[ 50%] Linking CXX static library ..\..\..\..\lib\libgtest_main.a
[ 50%] Built target gtest_main
Scanning dependencies of target ReverseTest
[ 57%] Building CXX object CMakeFiles/ReverseTest.dir/ReverseTest.cpp.obj
[ 64%] Building CXX object CMakeFiles/ReverseTest.dir/src/Reverse.cpp.obj
[ 71%] Linking CXX executable ReverseTest.exe
[ 71%] Built target ReverseTest
Scanning dependencies of target gmock
[ 78%] Building CXX object 3rd_party/google-test/googletest-build/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.obj
[ 85%] Linking CXX static library ..\..\..\..\lib\libgmock.a
[ 85%] Built target gmock
Scanning dependencies of target gmock_main
[ 92%] Building CXX object 3rd_party/google-test/googletest-build/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.obj
[100%] Linking CXX static library ..\..\..\..\lib\libgmock_main.a
[100%] Built target gmock_main



λ mingw32-make.exe  test
Running tests...
Test project C:/Users/crini/Documents/workspace/cmake_tutorials/11-google-test/build
    Start 1: reverse_class_test
1/1 Test #1: reverse_class_test ...............   Passed    0.08 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.09 sec

λ .\main.exe
!tset elgooG olleH
```
