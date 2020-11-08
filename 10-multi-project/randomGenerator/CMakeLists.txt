# Set the project name
project (randomGenerator)

# Add a library with the above sources
add_library(${PROJECT_NAME} src/RandomGenerator.cpp)
# To create an alias target run:
add_library(sub::randomGenerator ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
