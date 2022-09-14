cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(metal_project)

# Homebrew is needed
if(NOT(HOMEBREW_DIR))
    set(HOMEBREW_DIR "/opt/homebrew/lib")
endif()
if(NOT(HOMEBREW_INCLUDE))
    set(HOMEBREW_INCLUDE "/opt/homebrew/include")
endif()

add_subdirectory(normal_math)
add_subdirectory(metal_math)
add_subdirectory(metal_test)
add_subdirectory(metal_benchmark)