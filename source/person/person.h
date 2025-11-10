//
// Created by illusory on 2024/11/22.
//
#include "iostream"
#include <string>

#ifndef CPP_LEARN_PERSON_H
#define CPP_LEARN_PERSON_H

class Person {
public:
    static std::string animal;
//    explicit Person(int age) : age(age) {}

    Person() {
        std::cout << "person 构造函数调用" << std::endl;
    }

    explicit Person(const int &num) {
        age = num;
        std::cout << "person 有参构造函数调用" << std::endl;
    }

    Person(const Person &p) {
        age = p.age;
        std::cout << "person 拷贝构造函数调用" << std::endl;
    }

    ~Person() {
        std::cout << "Person 析构函数调用" << std::endl;
    }

    int age{};

    static void say() {
        std::cout << "我是人类!" << std::endl;
        std::cout << "喜欢吃" << Person::fruit << std::endl;
    }

    void sayAge() const {
        std::cout << "age is " << this->age << std::endl;
    }
private:
    static std::string fruit;
};
std::string Person::animal = "人类";
std::string Person::fruit = "apple";

#endif //CPP_LEARN_PERSON_H
