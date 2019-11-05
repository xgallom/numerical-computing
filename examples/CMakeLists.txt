file(GLOB_RECURSE files "src/*.cpp")

add_library(examples STATIC ${files})
target_include_directories(examples PUBLIC include)

target_link_libraries(examples PUBLIC numerical_computing)







