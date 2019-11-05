cmake_minimum_required(VERSION 3.15)
project(numerical_computing)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS iostreams system filesystem)

add_subdirectory(gnuplot_iostream)
add_subdirectory(symbolic_cpp)
add_subdirectory(numerical_computing)
add_subdirectory(examples)

add_executable(numerical_computing_exe main.cpp)
target_link_libraries(numerical_computing_exe examples)
