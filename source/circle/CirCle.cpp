//
// Created by illusory on 2024/11/22.
//
#include "iostream"
#include "CirCle.h"

using namespace std;


int main() {
    CirCle c1{};
    c1.m_r = 10;
    cout << c1.calculateZC() << endl;
    return 0;
}
