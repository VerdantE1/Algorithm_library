cmake_minimum_required(VERSION 3.28)

# 定义项目名称和 C++ 标准
project(Algorithms)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


# 包管理：引入 Catch2 库
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

# 定义算法库
add_library(algorithms
        src/search.cpp
)

# 为算法库设置头文件目录（推荐使用 target_include_directories）
target_include_directories(algorithms PUBLIC ${CMAKE_SOURCE_DIR}/include)

# 启用测试功能
enable_testing()

# 定义测试目标
add_executable(
        test_search test/test_search.cpp
)

# 链接测试目标与库
target_link_libraries(
        test_search PRIVATE Catch2::Catch2WithMain algorithms
)

# 自动发现测试
include(Catch)
catch_discover_tests(test_search)