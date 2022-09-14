cmake_minimum_required(VERSION 3.22)
if(NOT(CMAKE_CXX_COMPILER_LOADED))
    set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
project(normal_math)

add_library(normal_math INTERFACE include/normal.h include/normal_container_traits.h)
target_include_directories(normal_math INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
