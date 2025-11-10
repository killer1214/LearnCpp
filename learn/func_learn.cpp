//
// Created by illusory on 2024/11/22.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void func(int &a) {
    cout << "void func(int &a)" << endl;
}

void func(const int &a) {
    cout << "void func(const修饰成员函数.md int &a)" << endl;
}

void func(const int &a, int b=10) {
    cout << "void func(const修饰成员函数.md int &a)" << endl;
}

int main() {
    const int num = 10;
    func(num,);
    return 0;
}
