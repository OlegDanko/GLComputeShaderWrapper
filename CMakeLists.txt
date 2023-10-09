cmake_minimum_required(VERSION 3.14)

project(compute_shader LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(deps/gl_context)

add_library(compute_shader INTERFACE
    include/compute_shader/ComputeShaderBase.hpp
    include/compute_shader/TypeToFormat.hpp
)

target_include_directories(compute_shader INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/gl_context/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/include/compute_shader
)

target_link_libraries(compute_shader INTERFACE gl_context)
