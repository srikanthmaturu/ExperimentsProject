cmake_minimum_required(VERSION 3.5)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")
include(AppendCompilerFlags)

enable_testing()

project(ExperimentsProject)

append_cxx_compiler_flags("-msse4.2 -std=c++14 -Wall -DNDEBUG -fopenmp" "GCC" CMAKE_CXX_FLAGS)
append_cxx_compiler_flags("-O3 -ffast-math -funroll-loops" "GCC" CMAKE_CXX_FLAGS)

set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(${CMAKE_HOME_DIRECTORY}/include/
                    ${CMAKE_HOME_DIRECTORY}/src/)

ADD_EXECUTABLE(extract_kmers_from_kcfiles src/extractKMERSFromKCFiles.cpp)
MESSAGE("Target extract_kmers_from_kcfiles created.")

ADD_EXECUTABLE(generate_query_file src/generateQueryFile.cpp)
MESSAGE("Target generate_query_file created.")


