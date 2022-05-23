cmake_minimum_required(VERSION 3.0.0)
project(图
    VERSION 0.1.0
    LANGUAGES CXX)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++20" COMPILER_SUPPORTS_CXX20)

set( CMAKE_BUILD_TYPE "Debug" )#调试模式

set(SOURCES
    src/algorithms.cpp
    src/algorithms_impl.cpp
    src/graph_impl.cpp
    src/graph.cpp
    src/multi_graph_management.cpp
    src/multi_graph_management_impl.cpp
    src/utils.cpp 
    src/main.cpp
)#创建一个变量，名字叫SOURCE。它包含了所有的cpp文件。

add_executable(main ${SOURCES})

target_include_directories(main
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)#设置这个可执行文件hello_headers需要包含的库的路径

target_compile_features(main PRIVATE cxx_std_20)
set_target_properties(main PROPERTIES CXX_EXTENSIONS OFF)
