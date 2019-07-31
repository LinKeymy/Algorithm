//
//  main.cpp
//  permutations_submissions
//
//  Created by SteveLin on 2019/7/30.
//  Copyright © 2019 SteveLin. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

// https://leetcode-cn.com/problems/permutations/submissions/

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<vector<int>> tmp;
        vector<int> start = {nums[0]};
        res.push_back(start);
        for (int i = 1; i < nums.size(); ++i) {
            while (!res.empty()) {
                vector<int> bk = res.back();
                res.pop_back();
                for (int k = 0; k <= (int)bk.size() ; ++k) {
                    vector<int> new_n = bk;
                    new_n.insert(new_n.begin() + k, nums[i]);
                    tmp.push_back(new_n);
                }
            }
            while (!tmp.empty()) {
                res.push_back(tmp.back());
                tmp.pop_back();
            }
        }
        return res;
    };
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
