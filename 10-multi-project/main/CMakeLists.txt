project(main)

# Create the executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link the static library from subproject1 using it's alias sub::helloWorldPrinter
# Link the header only library from subproject2 using it's alias sub::randomGenerator
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
    sub::randomGenerator
    sub::helloWorldPrinter
)
