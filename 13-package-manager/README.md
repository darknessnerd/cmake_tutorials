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
CMake projects, and installing it globally for Visual Studio projects. 
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


