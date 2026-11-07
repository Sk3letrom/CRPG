cmake_minimum_required(VERSION 3.21)
project(CRPG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/third part/json" json)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/third part/raylib" raylib)

# Disable tileson tests to avoid missing test-maps path issue
set(BUILD_TESTS OFF CACHE BOOL "Build unit tests." FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/third part/tileson" tileson)

add_subdirectory(src)
