cmake_minimum_required(VERSION 3.15)
project(numerical_computing)

set(CMAKE_CXX_STANDARD 17)

add_executable(numerical_computing main.cpp)


add_subdirectory(examples)
target_link_libraries(numerical_computing PUBLIC examples)

add_subdirectory(symbolic_cpp)
target_link_libraries(numerical_computing PRIVATE symbolic_cpp)


add_subdirectory(gnuplot-iostream)
target_link_libraries(numerical_computing PUBLIC gnuplot-iostream)

target_include_directories(numerical_computing PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/gnuplot-iostream"
        )

find_package(Boost REQUIRED COMPONENTS iostreams system filesystem)
target_include_directories(numerical_computing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(numerical_computing PUBLIC ${Boost_LIBRARIES})


