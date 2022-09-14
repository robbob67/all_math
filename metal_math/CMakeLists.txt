cmake_minimum_required(VERSION 3.22)
if(NOT(CMAKE_CXX_COMPILER_LOADED))
    set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
project(metal_math)

set(METALADDER_INPUT_FILE "math.metal")
set(METALADDER_AIR_FILE "MyLibrary.air")
set(METALADDER_LIBRARY_FILE "default.metallib")

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${METALADDER_AIR_FILE}
        COMMAND xcrun -sdk macosx metal -c ${CMAKE_CURRENT_SOURCE_DIR}/${METALADDER_INPUT_FILE} -o ${CMAKE_CURRENT_BINARY_DIR}/${METALADDER_AIR_FILE}
        DEPENDS ${METALADDER_INPUT_FILE}
        VERBATIM)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${METALADDER_LIBRARY_FILE}
        COMMAND xcrun -sdk macosx metallib ${CMAKE_CURRENT_BINARY_DIR}/${METALADDER_AIR_FILE} -o ${CMAKE_CURRENT_BINARY_DIR}/${METALADDER_LIBRARY_FILE}
        DEPENDS ${METALADDER_AIR_FILE}
        VERBATIM)

add_custom_target(metalAirFile
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${METALADDER_AIR_FILE})
add_custom_target(metalAirLibrary
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${METALADDER_LIBRARY_FILE})

set(ADD_FOUNDATION_FRAMEWORK "-framework Foundation")
set(ADD_METAL_FRAMEWORK "-framework Metal")
set(ADD_METALKIT_FRAMEWORK "-framework MetalKit")
set(METAL_INCLUDE_DIR "metal")
set(CPP_RUNTIME_LIBRARY "-stdlib=libc++")
set(OBJ_C_NO_ARC "-fno-objc-arc")
set(G_FLAG "-g")
set(O_FLAG "-O2")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${ADD_FOUNDATION_FRAMEWORK}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${ADD_METAL_FRAMEWORK}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${ADD_METALKIT_FRAMEWORK}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CPP_RUNTIME_LIBRARY}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OBJ_C_NO_ARC}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${G_FLAG}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${O_FLAG}")

add_library(metal_math SHARED include/metal.h src/metal_allocator.cpp include/metal_allocator.h src/function.cpp include/function.h src/device.cpp src/device.h src/library.cpp src/library.h src/create_function.cpp include/create_function.h src/command_queue.cpp src/command_queue.h)
add_dependencies(metalAirLibrary metalAirFile)
add_dependencies(metal_math metalAirLibrary)
target_include_directories(metal_math PUBLIC
        ${METAL_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(metal_math PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR})
