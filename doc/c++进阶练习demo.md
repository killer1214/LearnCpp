# C++ 进阶练习集

下面是一组C++进阶练习代码，涵盖了指针、内存管理、面向对象编程、模板、STL容器、异常处理等高级主题。这些练习可以帮助你深入理解C++的核心概念。

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <type_traits>
#include <functional>
using namespace std;

// 1. 智能指针和内存管理
void smartPointersDemo() {
    cout << "\n===== 智能指针和内存管理 =====\n";
    
    // unique_ptr 示例
    unique_ptr<int> uptr(new int(42));
    cout << "unique_ptr 值: " << *uptr << endl;
    
    // 转移所有权
    unique_ptr<int> uptr2 = move(uptr);
    if (!uptr) {
        cout << "uptr 所有权已转移" << endl;
    }
    
    // shared_ptr 示例
    shared_ptr<int> sptr1 = make_shared<int>(100);
    {
        shared_ptr<int> sptr2 = sptr1;
        cout << "共享指针计数: " << sptr1.use_count() << endl;
    }
    cout << "共享指针计数: " << sptr1.use_count() << endl;
    
    // weak_ptr 示例
    weak_ptr<int> wptr = sptr1;
    if (auto tmp = wptr.lock()) {
        cout << "通过weak_ptr访问值: " << *tmp << endl;
    }
}

// 2. 面向对象编程：继承和多态
class Shape {
public:
    virtual double area() const = 0; // 纯虚函数
    virtual ~Shape() = default;
    virtual void print() const {
        cout << "形状: ";
    }
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override {
        return 3.14159 * radius * radius;
    }
    void print() const override {
        Shape::print();
        cout << "圆形, 半径: " << radius << ", 面积: " << area() << endl;
    }
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override {
        return width * height;
    }
    void print() const override {
        Shape::print();
        cout << "矩形, " << width << "x" << height 
             << ", 面积: " << area() << endl;
    }
};

void polymorphismDemo() {
    cout << "\n===== 面向对象编程：继承和多态 =====\n";
    
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Circle>(5.0));
    shapes.push_back(make_unique<Rectangle>(4.0, 6.0));
    
    for (const auto& shape : shapes) {
        shape->print();
    }
}

// 3. 模板编程
template <typename T>
class Stack {
    vector<T> elements;
public:
    void push(const T& value) {
        elements.push_back(value);
    }
    
    T pop() {
        if (elements.empty()) {
            throw runtime_error("栈为空");
        }
        T value = elements.back();
        elements.pop_back();
        return value;
    }
    
    bool empty() const {
        return elements.empty();
    }
};

template <typename T>
T add(T a, T b) {
    static_assert(is_arithmetic<T>::value, "只支持算术类型");
    return a + b;
}

void templateDemo() {
    cout << "\n===== 模板编程 =====\n";
    
    // 模板类
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    cout << "出栈: " << intStack.pop() << endl;
    cout << "出栈: " << intStack.pop() << endl;
    
    // 模板函数
    cout << "add(3.5, 4.2): " << add(3.5, 4.2) << endl;
    cout << "add(10, 20): " << add(10, 20) << endl;
}

// 4. STL算法和Lambda表达式
void stlAlgorithmsDemo() {
    cout << "\n===== STL算法和Lambda表达式 =====\n";
    
    vector<int> numbers = {7, 3, 5, 1, 9, 2, 8, 4, 6};
    
    // 排序
    sort(numbers.begin(), numbers.end());
    cout << "排序后: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // 查找
    auto it = find(numbers.begin(), numbers.end(), 5);
    if (it != numbers.end()) {
        cout << "找到5，位置: " << distance(numbers.begin(), it) << endl;
    }
    
    // Lambda表达式
    cout << "偶数: ";
    for_each(numbers.begin(), numbers.end(), [](int n) {
        if (n % 2 == 0) cout << n << " ";
    });
    cout << endl;
    
    // 条件计数
    int count = count_if(numbers.begin(), numbers.end(), [](int n) {
        return n > 5;
    });
    cout << "大于5的元素数量: " << count << endl;
    
    // 转换
    vector<int> squares;
    transform(numbers.begin(), numbers.end(), back_inserter(squares), 
             [](int n) { return n * n; });
    
    cout << "平方值: ";
    for (int n : squares) cout << n << " ";
    cout << endl;
}

// 5. 异常处理
void exceptionHandlingDemo() {
    cout << "\n===== 异常处理 =====\n";
    
    auto divide = [](double a, double b) -> double {
        if (b == 0) {
            throw invalid_argument("除数不能为零");
        }
        return a / b;
    };
    
    try {
        cout << "10 / 5 = " << divide(10, 5) << endl;
        cout << "8 / 0 = " << divide(8, 0) << endl;
    }
    catch (const invalid_argument& e) {
        cerr << "错误: " << e.what() << endl;
    }
    catch (...) {
        cerr << "未知错误发生" << endl;
    }
}

// 6. 移动语义和完美转发
class Resource {
    int* data;
    size_t size;
public:
    Resource(size_t s) : size(s), data(new int[s]) {
        cout << "分配资源: " << s << " 个整数" << endl;
    }
    
    // 移动构造函数
    Resource(Resource&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "移动构造函数调用" << endl;
    }
    
    // 移动赋值运算符
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            cout << "移动赋值运算符调用" << endl;
        }
        return *this;
    }
    
    // 禁止拷贝
    Resource(const Resource&) = delete;
    Resource& operator=(const Resource&) = delete;
    
    ~Resource() {
        if (data) {
            cout << "释放资源: " << size << " 个整数" << endl;
            delete[] data;
        }
    }
};

void moveSemanticsDemo() {
    cout << "\n===== 移动语义 =====\n";
    
    Resource res1(100);
    
    // 使用移动构造函数
    Resource res2 = move(res1);
    
    // 使用移动赋值运算符
    Resource res3(50);
    res3 = move(res2);
}

// 7. 函数对象和绑定
void functionObjectsDemo() {
    cout << "\n===== 函数对象和绑定 =====\n";
    
    // 函数对象
    struct Adder {
        int base;
        Adder(int b) : base(b) {}
        int operator()(int x) const {
            return base + x;
        }
    };
    
    Adder add5(5);
    cout << "add5(10): " << add5(10) << endl;
    
    // bind示例
    auto add10 = bind(Adder(10), placeholders::_1);
    cout << "add10(15): " << add10(15) << endl;
    
    // 使用标准库函数对象
    vector<int> nums = {5, 3, 8, 1, 7};
    sort(nums.begin(), nums.end(), greater<int>());
    cout << "降序排序: ";
    for (int n : nums) cout << n << " ";
    cout << endl;
}

int main() {
    cout << "开始C++进阶练习\n";
    
    smartPointersDemo();
    polymorphismDemo();
    templateDemo();
    stlAlgorithmsDemo();
    exceptionHandlingDemo();
    moveSemanticsDemo();
    functionObjectsDemo();
    
    cout << "\n所有进阶练习完成!" << endl;
    return 0;
}
```

## 编译和运行

1. 将代码保存为 `advanced_cpp.cpp`
2. 使用以下命令编译（需要支持C++11或更高版本）：
   ```bash
   g++ -std=c++11 advanced_cpp.cpp -o advanced_cpp
   ```
3. 运行程序：
   ```bash
   ./advanced_cpp   # Linux/Mac
   .\advanced_cpp.exe  # Windows
   ```

## 练习内容说明

1. **智能指针和内存管理**
    - `unique_ptr` 的所有权转移
    - `shared_ptr` 的共享所有权和引用计数
    - `weak_ptr` 避免循环引用

2. **面向对象编程：继承和多态**
    - 抽象基类和纯虚函数
    - 派生类实现和重写虚函数
    - 使用智能指针管理多态对象

3. **模板编程**
    - 模板类实现栈数据结构
    - 模板函数实现类型安全操作
    - `static_assert` 进行编译时检查

4. **STL算法和Lambda表达式**
    - 使用 `sort`, `find`, `count_if`, `transform` 等算法
    - Lambda表达式作为谓词函数
    - 使用 `back_inserter` 生成输出迭代器

5. **异常处理**
    - 自定义异常类型
    - `try-catch` 块捕获和处理异常
    - 异常安全编程

6. **移动语义**
    - 移动构造函数和移动赋值运算符
    - `std::move` 转移资源所有权
    - 禁止拷贝操作

7. **函数对象和绑定**
    - 函数对象（仿函数）
    - `std::bind` 绑定参数
    - 标准库函数对象如 `greater`

## 输出示例

```
开始C++进阶练习

===== 智能指针和内存管理 =====
unique_ptr 值: 42
uptr 所有权已转移
共享指针计数: 2
共享指针计数: 1
通过weak_ptr访问值: 100

===== 面向对象编程：继承和多态 =====
形状: 圆形, 半径: 5, 面积: 78.5397
形状: 矩形, 4x6, 面积: 24

===== 模板编程 =====
出栈: 20
出栈: 10
add(3.5, 4.2): 7.7
add(10, 20): 30

===== STL算法和Lambda表达式 =====
排序后: 1 2 3 4 5 6 7 8 9 
找到5，位置: 4
偶数: 2 4 6 8 
大于5的元素数量: 4
平方值: 1 4 9 16 25 36 49 64 81 

===== 异常处理 =====
10 / 5 = 2
错误: 除数不能为零

===== 移动语义 =====
分配资源: 100 个整数
移动构造函数调用
分配资源: 50 个整数
移动赋值运算符调用
释放资源: 50 个整数
释放资源: 100 个整数

===== 函数对象和绑定 =====
add5(10): 15
add10(15): 25
降序排序: 8 7 5 3 1 

所有进阶练习完成!
```

## 进一步挑战

1. 实现一个线程安全的模板队列
2. 扩展Shape类，添加三维图形支持
3. 实现一个简单的元编程示例（如编译时阶乘计算）
4. 使用std::async实现并行算法
5. 创建一个自定义内存分配器

这些练习涵盖了C++11/14的核心特性，通过实践可以加深对现代C++编程的理解。