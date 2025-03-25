//
// Created by Buzzlight on 2025/3/25.
//
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_DEFAULT_REPORTER_DETAIL_LEVEL_VERBOSE // 使用详细模式
#include <catch2/catch_all.hpp>
#include "algorithms/search.h"
#include <iostream>


TEST_CASE("Binary Search - Target Found", "[search]") {
    std::vector<int> data = {1, 3, 5, 7, 9, 11};
    REQUIRE(algorithms::binarySearch(data, 5) == 2); // 目标值 5 的索引是 2
    REQUIRE(algorithms::binarySearch(data, 1) == 0); // 目标值 1 的索引是 0
    REQUIRE(algorithms::binarySearch(data, 11) == 5); // 目标值 11 的索引是 5

    std::cout << "Test case 'Binary Search - Target Found' passed!" << std::endl;
}
TEST_CASE("Binary Search - Target Not Found", "[search]") {
    std::vector<int> data = {1, 3, 5, 7, 9, 11};
    REQUIRE(algorithms::binarySearch(data, 4) == -1); // 目标值 4 不存在
    REQUIRE(algorithms::binarySearch(data, 12) == -1); // 目标值 12 不存在

    std::cout << "Test case 'Binary Search - Target Not Found' passed!" << std::endl;

}
TEST_CASE("Binary Search - Empty Array", "[search]") {
    std::vector<int> data = {};
    REQUIRE(algorithms::binarySearch(data, 5) == -1); // 空数组中找不到任何值

    std::cout << "Test case 'Binary Search - Empty Array' passed!" << std::endl;
}