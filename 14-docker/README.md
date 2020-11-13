# Introduction

Our goal for this exercise is to build a C++ 
application with the latest stable versions of gcc and CMake, with a docker image
# Concepts

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

