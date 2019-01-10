# Top-level project configuration
cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

project("ZW1-Mlyn")

add_subdirectory("submodules")

# Include subdirectories
add_subdirectory("app")
add_subdirectory("gkom")
add_subdirectory("gl-cpp")
# add_subdirectory("util")
