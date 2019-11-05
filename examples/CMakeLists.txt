file(GLOB_RECURSE files "src/*.cpp")

add_library(examples STATIC ${files} include/project_1.h src/project_1.cpp include/project_2.h src/project_2.cpp)


target_include_directories(examples PUBLIC include)

target_include_directories(examples PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/gnuplot-iostream"
        )

target_link_libraries(examples PRIVATE symbolic_cpp)
target_link_libraries(examples PRIVATE "${PROJECT_SOURCE_DIR}/gnuplot-iostream")







