cmake_minimum_required(VERSION 3.16)

project(MAJ3 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(.)

set(CMAKE_CXX_FLAGS "-O2 -Werror -Wall -Wextra -fpic -flto -pipe -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG")

# Install inside the build directory.
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

enable_testing()

add_subdirectory(maj3)
add_subdirectory(test)
#add_subdirectory(doc)
