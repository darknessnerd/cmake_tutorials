# cmake_tutorials


<a href="https://www.buymeacoffee.com/darknessnerd"><img src="https://img.buymeacoffee.com/button-api/?text=Buy me chalk for Climbing&emoji=⛰️&slug=darknessnerd&button_colour=79D6B5&font_colour=ffffff&font_family=Comic&outline_colour=000000&coffee_colour=FFDD00"></a>


CMake is a cross-platform free and open-source software tool for managing the build process of software using a compiler-independent method. CMake is not a build system but rather it's a build-system generator. It supports directory hierarchies and applications that depend on multiple libraries. It is used in conjunction with native build environments such as Make, Qt Creator, Ninja, Android Studio, Apple's Xcode, and Microsoft Visual Studio. It has minimal dependencies, requiring only a C++ compiler on its own build system.


CMake can handle in-source and out-of-source builds, enabling several builds from the same source tree, and cross-compilation. The ability to build a directory tree outside the source tree is a key feature, ensuring that if a build directory is removed, the original source files remain unaffected.

# Flexible project structure
CMake can locate system-wide and user-specified executables, files, and libraries. These locations are stored in a cache, which can then be tailored before generating the target build files. The cache can be edited with a graphical editor, which is shipped with the CMake.

Complicated directory hierarchies and applications that rely on several libraries are well supported by CMake. For instance, CMake is able to accommodate a project that has multiple toolkits, or libraries that each have multiple directories. In addition, CMake can work with projects that require executables to be created before generating code to be compiled for the final application. Its open-source, extensible design allows CMake to be adapted as necessary for specific projects.

# IDEs configuration support
CMake can generate project files for several popular IDEs, such as Microsoft Visual Studio, Xcode, and Eclipse CDT. It can also produce build scripts for MSBuild or NMake on Windows; Unix Make on Unix-like platforms such as Linux, macOS, and Cygwin; and Ninja on both Windows and Unix-like platforms.

# Build process
The build process of a program or library with CMake takes place in two stages. First, standard build files are created (generated) from configuration files (CMakeLists.txt) which are written in CMake language. Then the platform's native build tools (native toolchain) are used for actual building of programs.

The build files are configured depending on used generator (e.g. Unix Makefiles for make). Advanced users can also create and incorporate additional makefile generators to support their specific compiler and OS needs. Generated files are typically placed (by using cmake flag) into a different from sources folder e.g. build/.

Each build project in turn contains a CMakeCache.txt file and CMakeFiles directory in every (sub-)directory of the projects (happened to be included by add_subdirectory(...) command earlier) helping to avoid or speed up regeneration stage once it's run over again.

# Types of build targets
Depending on CMakeLists.txt configuration the build files may be either executables, libraries (e.g. libxyz, xyz.dll etc), object file libraries or pseudo-targets (including aliases). Cmake can produce object files that can be linked against by executable binaries/libraries avoiding dynamic (run-time) linking and using static (compile-time) one instead. This enables flexibility in configuration of various optimizations.
