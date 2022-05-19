cmake_minimum_required(VERSION 3.0.0)
project(顺序线性表 VERSION 0.1.0)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++20" COMPILER_SUPPORTS_CXX20)


set(SOURCES
    src/file_operation.cpp 
    src/memory_operation.cpp 
    src/multi_list_management.cpp 
    src/utils.cpp
    src/sq_list.cpp
    src/main.cpp
)#创建一个变量，名字叫SOURCE。它包含了所有的cpp文件。

add_executable(main ${SOURCES})

target_compile_features(main PUBLIC cxx_std_11)
set_target_properties(main PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(main
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)#设置这个可执行文件hello_headers需要包含的库的路径
