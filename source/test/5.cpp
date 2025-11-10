//
// Created by illusory on 2025/6/22.
//

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <type_traits>
#include <functional>

using namespace std;

//1. 智能指针和内存管理
void smartPointerDemo() {
    cout << "\n===== 智能指针和内存管理 =====\n";

    // unique_ptr
    unique_ptr<int> uptr (new int(42));
//    unique_ptr<int> uptr1 = make_unique<int>(42);
    cout << "unique_ptr 值: " << *uptr << endl;

    // 转移所有权
    unique_ptr<int> uptr2 = std::move(uptr);
    if (!uptr) {
        cout << "uptr 所有权已转移" << endl;
        cout << "转移到uptr2: " << *uptr2 << endl;
    }

    int *num = uptr2.release();
    cout << *num << endl;
    delete num;

    // shared_ptr示例
    shared_ptr<int> sptr1 = make_shared<int>(100);
    {
        shared_ptr<int> sptr2 = sptr1;
        cout << "shared_pte引用后, 共享指针计数: " << sptr1.use_count() << endl;
    }
    cout << "共享指针计数: " << sptr1.use_count() << endl;

    weak_ptr<int> wptr = sptr1;
    cout << "weak_ptr引用后, 共享指针计数: " << sptr1.use_count() << endl;
    if (auto tmp = wptr.lock()) {
        cout << "weak_ptr访问后, 共享指针计数: " << sptr1.use_count() << endl;
        sptr1.reset();
        cout << "通过weak_ptr访问值: " << *tmp << endl;
    }
    cout << "weak_ptr访问释放后, 共享指针计数: " << sptr1.use_count() << endl;

}

// 2. 面向对象编程: 继承和多态
class Shape {
public:
    // 派生类必须重写（实现）所有的纯虚函数，否则派生类也会变成抽象类
    virtual double area() const = 0; //纯虚函数, 包含纯虚函数的类被称为抽象类
    // const表示这是一个 常量成员函数，向编译器承诺函数不会修改对象的状态（即不会修改类的成员变量）
    //除非变量被声明为 mutable

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

void polymorphisDemo() {
    cout << "\n===== 面向对象编程：继承和多态 =====\n";

    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Circle>(5.0));
    shapes.push_back(make_unique<Rectangle>(4.0, 6.0));

    for (const auto& shape : shapes) {
        shape->print();
    }
}

//3. 模板编程
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
    cout << "add(3.5, 4.2) = " << add(3.5, 4.2) << endl;
    cout << "add(10, 20) = " << add(10, 20) << endl;
}

// 4. STL算法和Lambda表达式
void stlAlgorithmDemo() {
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
        cout << "元素5，位置：" << distance(numbers.begin(), it) << endl;
    }

    // Lambda表达式
    cout << "偶数: ";
    for_each(numbers.begin(), numbers.end(), [](int n) {
        if (n % 2 == 0) cout << n << " ";
    });
    cout << endl;

    // 条件计数
    int count = count_if(numbers.begin(), numbers.end(), [](int n ){
        return n > 5;
    });
    cout << "元素大于5的数量: " << count << endl;

    // 转换
    vector<int> squares;
    transform(numbers.begin(), numbers.end(), back_inserter(squares), [](int n) {
        return n * n;
    });

    cout << "平方值: ";
    for (int n : squares) cout << n << " ";
    cout << endl;
}


//5. 异常处理
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
//    无符号整数类型, 专门用于表示内存中对象的大小和索引; 注意回绕行为
    size_t size;
public:
    Resource(size_t s) : size(s), data(new int[s]) {
        cout << "分配资源: " << s << " 个整数" << endl;
    }

    // 移动构造函数
    Resource(Resource&& other) noexcept
        : data(other.data), size(other.size){
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

    //使用移动构造函数
    Resource res2 = move(res1);

    // 使用移动赋值运算符
    Resource res3(50);
    res3 = move(res2);
}

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
    cout << "add5(10): " << add5(10) << endl;

    // bind 示例
    auto add10 = bind(Adder(10), placeholders::_1);
    cout << "add10(15): " << add10(15) << endl;
    cout << "add10(15): " << add10(15) << endl;

    // 使用标准库函数对象
    vector<int> nums = {5, 3, 8, 1, 7};
    sort(nums.begin(), nums.end(), greater<int>());
    cout << "降序排序: ";
    for (int n : nums) cout << n << " ";
    cout << endl;

}



int main()
{
    cout << "=== 学习开始 ===\n";
//    polymorphisDemo();
//    templateDemo();
//    stlAlgorithmDemo();
//    exceptionHandlingDemo();
//    moveSemanticsDemo();
    functionObjectsDemo();
    return 0;
}


