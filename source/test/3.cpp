//
// Created by illusory on 2024/12/1.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> pos(128, -1);
        int ans = 0;
        for (int i = 0, j = 0; i < s.length(); ++i) {
            j = max(j, pos[s[i]] + 1);
            ans = max(ans, i - j + 1);
            pos[s[i]] = i;
        }
        return ans;
    }
};

int main() {
    Solution s;
    string str1 = "abcabcbb";
    int res = s.lengthOfLongestSubstring(str1);
    cout << "result = " << res << endl;
    return 0;
}

