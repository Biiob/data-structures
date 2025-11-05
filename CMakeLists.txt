cmake_minimum_required(VERSION 3.5)
project(DataStructures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -O2)

# Enable testing globally
include(CTest)
enable_testing()

# Add the source directory (header-only library)
add_subdirectory(src)
# Add the tests
add_subdirectory(src/tests)