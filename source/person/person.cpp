//
// Created by illusory on 2024/11/22.
//
#include "iostream"
#include "person.h"

using namespace std;

void goWork(Person &p) {
    cout << "goWork" << endl;
    p.age = 20;
}

Person yourAge() {
    Person p;
    p.age = 18;
    return p;
}

int main() {
    int num = 21;
    Person per(21);
//    per.age = 19;
    Person pe2(per);
    Person::say();
    per.sayAge();

//    goWork(per);
//    Person p = yourAge();
    return 0;
}