以下是一些C++基础练习代码，涵盖了变量、控制流、函数、数组、字符串、结构体和类等核心概念。你可以将这些代码复制到本地编译执行：

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 1. 基本变量类型和控制流
void basicOperations() {
    cout << "\n===== 基本运算和控制流 =====\n";
    int a = 15, b = 4;
    double pi = 3.14159;
    
    // 算术运算
    cout << a << " + " << b << " = " << a + b << endl;
    cout << a << " / " << b << " = " << a / b << " (整数除法)" << endl;
    cout << pi << " * " << b << " = " << pi * b << endl;
    
    // 关系运算
    cout << a << " > " << b << " : " << (a > b) << endl;
    
    // 条件语句
    if (a % 2 == 0) {
        cout << a << " 是偶数" << endl;
    } else {
        cout << a << " 是奇数" << endl;
    }
    
    // 循环
    cout << "1-5的平方: ";
    for (int i = 1; i <= 5; i++) {
        cout << i * i;
        if (i < 5) cout << ", ";
    }
    cout << endl;
}

// 2. 函数使用
int add(int x, int y) {
    return x + y;
}

void functionDemo() {
    cout << "\n===== 函数使用 =====\n";
    int num1 = 23, num2 = 17;
    cout << num1 << " + " << num2 << " = " << add(num1, num2) << endl;
}

// 3. 数组和向量
void arrayAndVector() {
    cout << "\n===== 数组和向量 =====\n";
    // 传统数组
    int nums[5] = {2, 4, 6, 8, 10};
    cout << "数组元素: ";
    for (int i = 0; i < 5; i++) {
        cout << nums[i] << " ";
    }
    
    // 向量容器
    vector<string> fruits = {"苹果", "香蕉", "橙子"};
    fruits.push_back("葡萄"); // 添加元素
    
    cout << "\n水果列表: ";
    for (const auto& fruit : fruits) {
        cout << fruit << " ";
    }
    cout << endl;
}

// 4. 字符串操作
void stringOperations() {
    cout << "\n===== 字符串操作 =====\n";
    string greeting = "Hello, C++ World!";
    
    cout << "原始字符串: " << greeting << endl;
    cout << "字符串长度: " << greeting.length() << endl;
    cout << "第一个单词: " << greeting.substr(0, 5) << endl;
    
    // 字符串连接
    string name = "Alice";
    string message = "你好, " + name + "!";
    cout << message << endl;
}

// 5. 结构体和类
struct Point {
    double x;
    double y;
    
    void print() {
        cout << "(" << x << ", " << y << ")";
    }
};

class Rectangle {
private:
    double width;
    double height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    double area() {
        return width * height;
    }
    
    void describe() {
        cout << width << "x" << height 
             << " 矩形, 面积: " << area();
    }
};

void structAndClassDemo() {
    cout << "\n===== 结构体和类 =====\n";
    
    // 结构体使用
    Point p1 = {3.5, 2.8};
    cout << "点坐标: ";
    p1.print();
    cout << endl;
    
    // 类使用
    Rectangle rect(5.0, 3.0);
    cout << "矩形信息: ";
    rect.describe();
    cout << endl;
}

int main() {
    cout << "开始C++基础练习\n";
    
    basicOperations();
    functionDemo();
    arrayAndVector();
    stringOperations();
    structAndClassDemo();
    
    cout << "\n所有练习完成!" << endl;
    return 0;
}
```

### 如何运行代码：
1. 将代码保存为 `cpp_basics.cpp`
2. 使用以下命令编译（需安装g++）：
   ```bash
   g++ -std=c++11 cpp_basics.cpp -o cpp_basics
   ```
3. 运行程序：
   ```bash
   ./cpp_basics   # Linux/Mac
   .\cpp_basics.exe  # Windows
   ```

### 练习包含内容：
1. **基本运算**：整数/浮点数运算、关系运算
2. **控制流**：条件语句(if-else)、循环(for)
3. **函数**：定义和调用函数
4. **数组和向量**：传统数组和动态数组(vector)
5. **字符串**：基本操作和拼接
6. **结构体和类**：创建结构体、实现类封装

### 输出示例：
```
开始C++基础练习

===== 基本运算和控制流 =====
15 + 4 = 19
15 / 4 = 3 (整数除法)
3.14159 * 4 = 12.5664
15 > 4 : 1
15 是奇数
1-5的平方: 1, 4, 9, 16, 25

===== 函数使用 =====
23 + 17 = 40

===== 数组和向量 =====
数组元素: 2 4 6 8 10 
水果列表: 苹果 香蕉 橙子 葡萄 

===== 字符串操作 =====
原始字符串: Hello, C++ World!
字符串长度: 17
第一个单词: Hello
你好, Alice!

===== 结构体和类 =====
点坐标: (3.5, 2.8)
矩形信息: 5x3 矩形, 面积: 15

所有练习完成!
```

你可以通过修改代码中的数值和添加新功能来进一步练习。例如尝试添加：
- 计算斐波那契数列
- 实现冒泡排序
- 创建更复杂的类继承结构
- 文件读写操作
- 异常处理等