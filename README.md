# 算法库与单元测试项目

本项目是一个通用算法库，包含多种经典算法的实现，并使用 [Catch2](https://github.com/catchorg/Catch2) 框架进行单元测试。项目旨在提供高质量的算法实现和可靠的测试覆盖，方便学习、使用和扩展。

---

## **1. 项目简介**

- **主要功能**：
  - 提供常用算法的实现（如二分搜索、排序、图算法等）。
  - 通过单元测试验证算法的正确性，确保代码质量。
- **使用场景**：
  - 学习算法基础知识。
  - 在工程项目中复用高效的算法实现。
  - 作为代码库扩展新算法。

---

## **2. 项目依赖的远程库**

### **Catch2 测试框架**
- **用途**：用于编写和运行单元测试。
- **集成方式**：通过 CMake 的 `FetchContent` 模块自动下载和集成。
- **来源**：[Catch2 官方仓库](https://github.com/catchorg/Catch2)。

在 `CMakeLists.txt` 文件中通过以下代码引入 Catch2：
```cmake
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0 # 指定版本号
)
FetchContent_MakeAvailable(Catch2)
target_link_libraries(test_algorithms PRIVATE Catch2::Catch2WithMain)
```

## **3.目前支持的算法函数**

### 3.1 二分查找
```cpp
int binarySearch(const std::vector<int>& nums, int target);
```
