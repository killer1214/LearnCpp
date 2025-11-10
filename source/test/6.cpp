//
// Created by illusory on 2025/6/22.
//

#include <memory>
#include <iostream>

using namespace std;

class Child;  // 前向声明

class Parent {
public:
    std::shared_ptr<Child> child;  // 持有 Child 的共享指针
    ~Parent() { std::cout << "Parent destroyed\n"; }
};

class Child {
public:
    std::weak_ptr<Parent> parent;  // 持有 Parent 的共享指针 ❌
    ~Child() { std::cout << "Child destroyed\n"; }
};

int main() {
    {
        auto parent = std::make_shared<Parent>();
        auto child = std::make_shared<Child>();
        cout << "child: " << child.use_count() << endl;

        parent->child = child;   // Parent 持有 Child
        cout << "parent: " << parent.use_count() << endl;
        cout << "child: " << child.use_count() << endl;

        child->parent = parent;  // Child 持有 Parent → 形成循环引用
        cout << "parent: " << parent.use_count() << endl;
    }  // 离开作用域时，对象不会被销毁！

    // 输出：无任何析构信息 → 内存泄漏
    return 0;
}