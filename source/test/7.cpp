//
// Created by illusory on 2025/6/30.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n); // 创建大小为n的vector

    for (auto num : arr) {
        cout << num << " - ";
    }
    cout << endl;
}

