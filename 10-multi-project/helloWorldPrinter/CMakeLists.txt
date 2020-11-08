# Set the project name
project (helloWorldPrinter)

#INTERFACE target to allow creating a target without any build output.
add_library(${PROJECT_NAME} INTERFACE)
add_library(sub::helloWorldPrinter ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)
