file(GLOB_RECURSE files "src/*.cpp")

add_library(numerical_computing STATIC ${files})
target_include_directories(numerical_computing PUBLIC include ${Boost_INCLUDE_DIR})

target_link_libraries(numerical_computing PUBLIC ${Boost_LIBRARIES} gnuplot_iostream symbolic_cpp)
