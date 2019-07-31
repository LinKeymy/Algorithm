//
//  main.cpp
//  flatten-binary-tree-to-linked-list
//
//  Created by SteveLin on 2019/7/31.
//  Copyright © 2019 SteveLin. All rights reserved.
//

// https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/

#include <iostream>
#include <vector>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    void flatten(TreeNode* root) {
        vector<TreeNode* > v;
        flatten(root, v);
        for (int i = 1; i < v.size() ; ++i) {
            v[i-1]->right = v[i];
            v[i-1]->left = nullptr;
            v[i]->left = nullptr;
        }
        root = v[0];
    }
    
    void flatten(TreeNode* node,vector<TreeNode* > &v) {
        if (node == nullptr) return;
        v.push_back(node);
        if (node->left != nullptr) {
            flatten(node->left,v);
        }
        if (node->right != nullptr) {
            flatten(node->right,v);
        }
    }
};

int main(int argc, const char * argv[]) {
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    Solution s;
    s.flatten(root);
    return 0;
}
