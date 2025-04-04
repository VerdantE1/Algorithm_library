cmake_minimum_required(VERSION 3.28)

project(Algorithms)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置可执行输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 添加算法库
add_library(algorithms
        src/String.cpp
        include/tools/tools.h
        include/tools/StateEncoder.h
        include/tools/FastStateEncoder.h
        include/array/SortedArrayUtils.h
        include/array/SortedArrayPairUtils.h
        src/SortedArrayUtils.cpp
        include/array/IrrgularArray.h
)

# 设置算法库的头文件路径
target_include_directories(algorithms
        PUBLIC ${CMAKE_SOURCE_DIR}/include
)

# 添加 main.cpp
add_executable(main
        main.cpp
)

# 链接算法库
target_link_libraries(main PRIVATE algorithms)

# 给 main.cpp 设置头文件路径
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)