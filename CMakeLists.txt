cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
message(STATUS "CMake version: ${CMAKE_VERSION}")

project(cpd_project LANGUAGES CUDA CXX)

set(CMAKE_CUDA_ARCHITECTURES "70")
set(CMAKE_CUDA_RUNTIME_LIBRARY, "Shared")

find_package(CUDAToolkit REQUIRED)
enable_language(CUDA)
include(CheckLanguage)
check_language(CUDA)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB source_files "${CMAKE_SOURCE_DIR}/src/*.cpp"
     "${CMAKE_SOURCE_DIR}/lib/lodepng/lodepng.h"
     "${CMAKE_SOURCE_DIR}/lib/lodepng/lodepng.cpp")
file(GLOB cuda_source_files "${CMAKE_SOURCE_DIR}/src/*.cu")

add_library(cpd_lib STATIC "${source_files}" "${cuda_source_files}")
target_compile_features(cpd_lib PUBLIC cxx_std_20)
target_include_directories(
  cpd_lib
  PUBLIC "${CMAKE_SOURCE_DIR}/src" "${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}"
         "${CMAKE_SOURCE_DIR}/lib")
target_link_libraries(cpd_lib PUBLIC CUDA::cudart)
set_target_properties(cpd_lib PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

# target_compile_options(cpd_lib PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:
# --generate-line-info --use_fast_math --relocatable-device-code=true >)

add_executable(cpd_app "${CMAKE_SOURCE_DIR}/app.cpp")
target_compile_features(cpd_app PUBLIC cxx_std_20)
target_include_directories(cpd_app PUBLIC "${CMAKE_SOURCE_DIR}/src")
target_link_libraries(cpd_app PRIVATE cpd_lib)

execute_process(
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_SOURCE_DIR}/res
          ${PROJECT_BINARY_DIR}/res RESULT_VARIABLE exitcode)
