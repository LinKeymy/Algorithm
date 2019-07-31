//
//  main.cpp
//  count-complete-tree-nodes
//
//  Created by SteveLin on 2019/7/30.
//  Copyright © 2019 SteveLin. All rights reserved.
//

// https://leetcode-cn.com/problems/count-complete-tree-nodes/




#include <iostream>

using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {};
};


#include <queue>
class Solution {
    
public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) return 0;
        queue<TreeNode *> q;
        q.push(move(root));
        int cout = 1;
        while (!q.empty()) {
            if (q.front()->left != nullptr) {
                q.push(move(q.front()->left));
                ++cout;
            }
            if (q.front()->right != nullptr) {
                q.push(move(q.front()->right));
                ++cout;
            }
            q.pop();
        }
        return cout;
    };
};

int main(int argc, const char * argv[]) {
    return 0;
}
