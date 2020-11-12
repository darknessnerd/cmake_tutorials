# Introduction

Our goal for this exercise is to build a C++ 
application with the latest stable versions of gcc and CMake, have that build execute on the 
Travis-CI services

# Concepts

## The Application

For the purpose of example we have a trivial program that we will pretend 
– for the sake of argument – absolutely requires the latest version of 
CMake and a fairly recent version of Clang.

```

```

## Docker Build Container

Our first step is to create a Docker container that is capable of building our application.

```

```
Minimal C++ development environment including gcc, CMake, cppcheck using Alpine Linux

Docker makes it easy to create a repeatable process for constructing specialized systems like this but it
is up to the developer to make sure it all works.

When developing locally we can use the following commands.

```
λ docker build .

λ docker images
REPOSITORY          TAG                 IMAGE ID            CREATED              SIZE
<none>              <none>              af2476fde736        About a minute ago   258MB

docker run --rm -it -v $(pwd):/project <IMAGE_ID> "mkdir -p build && cd build && cmake .. && make"

```

Shell Access

```
docker run --rm -it --entrypoint bash -v $(pwd):/project <IMAGE_ID>
```


Minimal C++ development environment including gcc, CMake, cppcheck and conan, using Alpine Linux
## Travis-CI

I chose Travis-CI for this example because it is free and transparent for open-source projects and – at the 
time of writing – has aging C++ support. At my job I am working with very old CI platforms that take 
months to get even the smallest changes made. For my purposes building C++ applications on Travis-CI 
is a good analog for building, well, anything at work. One thing my production CI infrastructure has 
in common with Travis-CI is the ability to use Docker containers.

The Travis-CI file for a container-based build is surprisingly similar to a normal build. There is a bit
more setup and the build commands are executed using the “docker exec” command.

```

```