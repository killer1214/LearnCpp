# C++ 成员函数后的 `const` 修饰符详解

在 C++ 中，成员函数名称后添加 `const` 修饰符表示这是一个**常量成员函数**（const member function），它向编译器承诺该函数不会修改对象的状态（即不会修改类的成员变量）。

## 核心作用

1. **对象状态保护**：
    - 禁止函数修改类的成员变量（除非变量被声明为 `mutable`）
    - 任何修改成员变量的尝试都会导致编译错误

2. **常量对象支持**：
    - 允许常量对象调用成员函数
    - 没有 `const` 修饰的成员函数无法被常量对象调用

## 语法格式

```cpp
class MyClass {
public:
    // 常量成员函数
    return_type functionName(parameters) const;
    
    // 非常量成员函数
    return_type functionName(parameters);
};
```

## 关键特性

### 1. 常量对象与函数调用

```cpp
class Counter {
    int count = 0;
public:
    void increment() { count++; }       // 非常量成员函数
    int getCount() const { return count; } // 常量成员函数
};

int main() {
    Counter c1;
    const Counter c2;
    
    c1.increment();  // 正确：非常量对象调用非常量函数
    c1.getCount();   // 正确：非常量对象调用常量函数
    
    // c2.increment(); // 错误！常量对象不能调用非常量函数
    c2.getCount();    // 正确：常量对象调用常量函数
}
```

### 2. 基于常量性的函数重载

C++ 允许同时存在常量版本和非常量版本的成员函数，编译器会根据调用对象的常量性自动选择：

```cpp
class TextBuffer {
    std::string text;
public:
    // 非常量版本：允许修改
    char& operator[](size_t pos) {
        return text[pos];
    }
    
    // 常量版本：只读访问
    const char& operator[](size_t pos) const {
        return text[pos];
    }
};

int main() {
    TextBuffer buffer;
    const TextBuffer& constRef = buffer;
    
    buffer[0] = 'A';     // 调用非常量版本
    char c = constRef[0]; // 调用常量版本
    
    // constRef[0] = 'B'; // 错误！常量版本返回const引用
}
```

### 3. `mutable` 成员变量

如果需要常量成员函数修改某些特殊成员变量，可以使用 `mutable` 修饰符：

```cpp
class AccessLogger {
    mutable int accessCount = 0; // 可以在常量函数中修改
    std::string data;
public:
    const std::string& getData() const {
        accessCount++; // 允许修改 mutable 成员
        return data;
    }
};
```

## 最佳实践

1. **尽量使用 `const`**：
   ```cpp
   // 推荐做法：不修改状态的函数都声明为 const
   int getValue() const { return value; }
   void printInfo() const { /* 只读操作 */ }
   ```

2. **正确重载常量/非常量版本**：
   ```cpp
   // 提供成对的常量/非常量版本
   const T& get() const;
   T& get();
   ```

3. **在函数参数中使用常量引用**：
   ```cpp
   // 正确：避免拷贝，同时保证不修改对象
   void processObject(const MyClass& obj) {
       obj.constMethod(); // 需要obj有const方法
   }
   ```

## 常见错误

```cpp
class Example {
    int value;
public:
    // 错误：试图在常量函数中修改成员
    void setValue(int v) const {
        // value = v; // 编译错误！
    }
    
    // 错误：常量对象调用非常量函数
    void test() {
        const Example e;
        // e.setValue(10); // 编译错误！
    }
};
```

## 总结：`const` 成员函数的作用

| 场景 | 常量成员函数 (`const`) | 非常量成员函数 |
|------|------------------------|----------------|
| **修改成员变量** | ✗ 禁止 | ✓ 允许 |
| **常量对象调用** | ✓ 允许 | ✗ 禁止 |
| **非常量对象调用** | ✓ 允许 | ✓ 允许 |
| **返回类型** | 通常返回 `const` 引用或值 | 通常返回非 `const` 引用 |
| **典型用途** | Getter 方法、只读操作 | Setter 方法、状态修改操作 |

正确使用 `const` 成员函数是编写健壮、安全 C++ 代码的关键，它能：
- 提高代码可读性和可维护性
- 在编译时捕获意外修改对象状态的错误
- 支持更灵活的对象使用方式（特别是常量对象）
- 为函数重载提供更多可能性

**设计原则**：如果一个成员函数不需要修改对象状态，就应该将其声明为 `const`。