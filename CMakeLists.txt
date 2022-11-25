cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
message(STATUS "CMake version: ${CMAKE_VERSION}")

project(cpd_project LANGUAGES CUDA CXX)

option(USE_CUDA "Use CUDA" ON)

file(GLOB source_files "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB cuda_source_files "${CMAKE_SOURCE_DIR}/src/*.cu" "${CMAKE_SOURCE_DIR}/src/*.cuh")

add_library(cpd_lib STATIC source_files cuda_source_files)

target_compile_features(cpd_lib PUBLIC cxx_std_20)
target_include_directories(cpd_lib PUBLIC "${CMAKE_SOURCE_DIR}/src")
set_target_properties(cpd_lib PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_compile_options(cpd_lib PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:
                       --generate-line-info
                       --use_fast_math
                       --relocatable-device-code=true
                       >)

add_executable(cpd_app "${CMAKE_SOURCE_DIR}/app.cpp")
target_compile_features(cpd_app PUBLIC cxx_std_20)
target_include_directories(cpd_app PUBLIC "${CMAKE_SOURCE_DIR}/src")
target_link_libraries(cpd_app PRIVATE cpd_lib)
