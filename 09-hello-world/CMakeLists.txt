cmake_minimum_required(VERSION 3.5)

# Set the project name
project (third_party_include)

# find a curl install with the libraries filesystem and system
find_package(CURL 7.73.0 REQUIRED)
message(${CURL_LIBRARIES})
message(${CURL_INCLUDE_DIRS})
# check if curl was found
if(CURL_FOUND)
    message ("curl found")
else()
    message (FATAL_ERROR "Cannot find CURL")
endif(CURL_FOUND)


#Set include dir
include_directories( ${CURL_INCLUDE_DIRS} )


# Add an executable
add_executable(third_party_include main.cpp)

# link against the curl libraries
target_link_libraries( third_party_include PRIVATE CURL::libcurl)
