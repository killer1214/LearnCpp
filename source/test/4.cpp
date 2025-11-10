//
// Created by illusory on 2024/12/1.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size() + nums2.size();
        if (n % 2 == 0) {
            int left = find(nums1, 0, nums2, 0, n / 2);
            int right = find(nums1, 0, nums2, 0, n / 2 + 1);
            return (left + right) / 2.0;
        }
        else {
            return find(nums1, 0, nums2, 0, n / 2 + 1);
        }
    }

    int find(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
//        默认nums1的长度小于nums2的长度
        if (nums1.size() - i > nums2.size() - j) {
            return find(nums2, j, nums1, i, k);
        }
        if (nums1.size() == i) return nums2[j + k - 1];
    }
};

int main() {
    Solution s;
    vector<int> num1 = {1,2};
    vector<int> num2 = {3,4};
    double res = s.findMedianSortedArrays(num1, num2);
    cout << "result = " << res << endl;
    return 0;
}