project(polyloader)
cmake_minimum_required(VERSION 3.10)

# Load the Sedeen dependencies
find_package(SEDEENSDK REQUIRED
             HINTS ../../..
             "$ENV{PROGRAMFILES}/Sedeen Viewer SDK/v5.4.2.20190715/msvc2017")

link_directories("${SEDEENSDK_LIBRARY_DIR}")
include_directories("${SEDEENSDK_INCLUDE_DIR}")

# Enable C++17 features
set(CMAKE_CXX_STANDARD 17)

# Build the plugin as a library
add_library(polyloader MODULE polyloader.cpp polyloader.hpp)

# Link the library against the Sedeen libraries
target_link_libraries(polyloader ${SEDEENSDK_LIBRARIES})

# Install the plugin in the sedeen plugins directory
# if(${PATHCORE_FOUND})
#   install(TARGETS Threshold_Example
#           LIBRARY DESTINATION "${PATHCORE_DIR}/plugins")
# endif()