### C++ API 详细使用指南：`std::vector` 容器

#### 一、`std::vector` 简介
`std::vector` 是 C++ 标准模板库（STL）中的动态数组容器，提供高效的随机访问和动态内存管理。核心特性：
- **动态扩容**：自动处理内存分配
- **连续存储**：支持指针算术操作
- **时间复杂度**：
    - 随机访问：O(1)
    - 尾部插入/删除：平均 O(1)
    - 中间插入/删除：O(n)

---

#### 二、基础 API 使用示例
```cpp
#include <iostream>
#include <vector>

int main() {
    // 1. 初始化
    std::vector<int> vec = {1, 2, 3};  // 初始化列表
    std::vector<int> vec2(5, 10);      // 5个元素，每个值为10

    // 2. 添加元素
    vec.push_back(4);       // 尾部插入：{1,2,3,4}
    vec.emplace_back(5);    // 高效尾部构造：{1,2,3,4,5}
    vec.insert(vec.begin() + 1, 9);  // 位置插入：{1,9,2,3,4,5}

    // 3. 访问元素
    std::cout << "Element at 2: " << vec[2] << '\n';       // 无边界检查
    std::cout << "Element at 2: " << vec.at(2) << '\n';    // 有边界检查
    std::cout << "First: " << vec.front() << '\n';         // 首元素
    std::cout << "Last: " << vec.back() << '\n';           // 末元素

    // 4. 删除元素
    vec.pop_back();                      // 删除尾部：{1,9,2,3,4}
    vec.erase(vec.begin() + 1);          // 删除位置1：{1,2,3,4}
    vec.erase(vec.begin(), vec.begin()+2); // 删除范围：{3,4}

    // 5. 容量操作
    std::cout << "Size: " << vec.size() << '\n';
    std::cout << "Capacity: " << vec.capacity() << '\n';
    vec.shrink_to_fit();  // 释放多余容量

    // 6. 遍历
    for(int num : vec) {  // 范围for循环
        std::cout << num << " ";
    }
    for(auto it = vec.begin(); it != vec.end(); ++it) {  // 迭代器
        *it += 10;  // 修改元素
    }

    return 0;
}
```

---

#### 三、进阶 API 技巧
1. **移动语义优化**
```cpp
std::vector<std::string> createStrings() {
    std::vector<std::string> v;
    v.emplace_back("Avoids");  // 避免临时对象
    v.push_back(std::move("move"));  // 移动语义
    return v;  // 返回值优化（RVO）
}
```

2. **预留空间减少分配**
```cpp
std::vector<int> data;
data.reserve(1000);  // 预分配内存
for(int i=0; i<1000; ++i) {
    data.emplace_back(i);  // 无重新分配开销
}
```

3. **自定义类型存储**
```cpp
struct Point {
    int x, y;
    Point(int a, int b) : x(a), y(b) {}
};

std::vector<Point> points;
points.emplace_back(1, 2);  // 直接构造
```

---

#### 四、进阶练习 Demo
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // 1. 矩阵乘法
    std::vector<std::vector<int>> matrixA = {{1,2}, {3,4}};
    std::vector<std::vector<int>> matrixB = {{5,6}, {7,8}};
    std::vector<std::vector<int>> result(2, std::vector<int>(2, 0));

    for(size_t i=0; i<matrixA.size(); ++i) {
        for(size_t j=0; j<matrixB[0].size(); ++j) {
            for(size_t k=0; k<matrixA[0].size(); ++k) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    // 2. 自定义排序
    std::vector<std::pair<int, std::string>> students = {
        {90, "Alice"}, {85, "Bob"}, {95, "Charlie"}
    };
    std::sort(students.begin(), students.end(), 
        [](const auto& a, const auto& b) {
            return a.first > b.first;  // 按分数降序
        });

    // 3. 高效去重
    std::vector<int> nums = {5, 2, 2, 3, 3, 3, 1};
    std::sort(nums.begin(), nums.end());
    auto last = std::unique(nums.begin(), nums.end());
    nums.erase(last, nums.end());  // {1,2,3,5}

    // 4. 内存池模拟
    constexpr int POOL_SIZE = 100;
    std::vector<int> memoryPool;
    memoryPool.reserve(POOL_SIZE);

    auto allocate = [&](int size) -> int* {
        if(memoryPool.size() + size > POOL_SIZE) 
            return nullptr;
        int* ptr = &memoryPool[memoryPool.size()];
        memoryPool.resize(memoryPool.size() + size);
        return ptr;
    };

    int* block = allocate(10);  // 分配10个int

    // 输出结果
    std::cout << "Matrix Multiply:\n";
    for(const auto& row : result) {
        for(int val : row) std::cout << val << " ";
        std::cout << '\n';
    }

    std::cout << "\nTop Student: " 
              << students[0].second << " (" 
              << students[0].first << ")\n";

    std::cout << "\nUnique Nums: ";
    for(int n : nums) std::cout << n << " ";

    return 0;
}
```

---

#### 五、关键注意事项
1. **迭代器失效**：
    - `push_back`/`insert` 可能使所有迭代器失效
    - `erase` 使被删位置后的迭代器失效
2. **性能陷阱**：
    - 避免在循环中多次调用 `size()`（缓存结果）
    - 优先用 `emplace_back` 替代 `push_back`
3. **内存管理**：
    - `clear()` 不释放内存（容量不变）
    - `shrink_to_fit()` 可减少容量到匹配大小
4. **异常安全**：
    - 基本操作提供强异常保证
    - 自定义类型需确保拷贝构造函数不抛异常

通过掌握这些技巧，可高效利用 `std::vector` 解决复杂问题。实际开发中应结合 `std::array`（固定大小）、`std::deque`（双端队列）等容器选择最佳工具。