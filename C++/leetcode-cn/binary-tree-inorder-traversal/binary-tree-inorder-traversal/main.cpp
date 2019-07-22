//
//  main.cpp
//  binary-tree-inorder-traversal
//
//  Created by SteveLin on 2019/7/22.
//  Copyright © 2019 unixlin. All rights reserved.
//

#include "BinarySearchTree.hpp"
#include <vector>

using namespace std;
class BinarySearchTree_Inoder: public BinarySearchTree<int> {
    
    void inorderTraversal_recuision(BinaryNode<int> * node,vector<int> &v) {
        if (node == nullptr) return;
        if (node->left != nullptr) {
            inorderTraversal_recuision(node->left,v);
        }
        v.push_back(node->m_element);
        if (node->right != nullptr) {
            inorderTraversal_recuision(node->right,v);
        }
    }
    
    void preorderTraversal_recuision(BinaryNode<int> * node,vector<int> &v) {
        if (node == nullptr) return;
        
        v.push_back(node->m_element);
        if (node->left != nullptr) {
            preorderTraversal_recuision(node->left,v);
        }
        if (node->right != nullptr) {
            preorderTraversal_recuision(node->right,v);
        }
    }
    
    vector<int> preorderTraversal(BinaryNode<int> * t) {
        vector<int> v;
        stack<BinaryNode<int> *> st;
        if (t != nullptr) st.push(t);
        while (!st.empty()) {
            t = st.top();
            st.pop();
            v.push_back(t->m_element);
            if (t->right != nullptr) {
                st.push(t->right);
            }
            if (t->left != nullptr) {
                st.push(t->left);
            }
        }
        return v;
    }
    
    /*
     vector<int> postorderTraversal(TreeNode * t) {
     vector<int> v;
     stack<TreeNode *> st;
     TreeNode * last_t = nullptr;
     if (t != nullptr) st.push(t);
     while (!st.empty()) {
     t = st.top();
     if ((t->left == nullptr && t->right == nullptr) || t->left == last_t || t->right == last_t) {
     v.push_back(t->val);
     last_t = t;
     st.pop();
     continue;
     } else {
     if (t->right != nullptr) {
     st.push(t->right);
     }
     if (t->left != nullptr) {
     st.push(t->left);
     }
     }
     
     }
     return v;
     }
     */
    vector<int> postorderTraversal(BinaryNode<int> * t) {
        vector<int> v;
        stack<BinaryNode<int> *> st;
        BinaryNode<int> * last_t = nullptr;
        if (t != nullptr) st.push(t);
        while (!st.empty()) {
            t = st.top();
            if ((t->left == nullptr && t->right == nullptr) || t->left == last_t || t->right == last_t) {
                v.push_back(t->m_element);
                last_t = t;
                st.pop();
                continue;
            } else {
                if (t->right != nullptr) {
                    st.push(t->right);
                }
                if (t->left != nullptr) {
                    st.push(t->left);
                }
            }
  
        }
        return v;
    }

    vector<int> inorderTraversal(BinaryNode<int> * t) {
        vector<int> v;
        stack<BinaryNode<int> *> st;
        while (1) {
            if (t != nullptr) {
                st.push(t);
                t = t->left;
            }
            if (t == nullptr) {
                if (st.empty()) return v;
                BinaryNode<int> * node = st.top();
                st.pop();
                v.push_back(node->m_element);
                t = node->right;
            }
        }
        return v;
    }
    
public:
    void inorderTraversal() {
        vector<int> v = inorderTraversal(root);
        auto it = v.begin();
        auto end = v.end();
        while (it != end) {
            cout << *it << endl;
            ++it;
        }
    }
    
    void preorderTraversal() {
        vector<int> v = preorderTraversal(root);
//        preorderTraversal_recuision(root,v);
        auto it = v.begin();
        auto end = v.end();
        while (it != end) {
            cout << *it << endl;
            ++it;
        }
    }
    
    void postorderTraversal() {
        vector<int> v = postorderTraversal(root);
        auto it = v.begin();
        auto end = v.end();
        while (it != end) {
            cout << *it << endl;
            ++it;
        }
    }
    
};


int main(int argc, const char * argv[]) {
    BinarySearchTree_Inoder bst;
    bst.insert(7);
    bst.insert(4);
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    bst.insert(5);
    bst.insert(9);
    bst.insert(8);
    bst.insert(11);
    bst.insert(10);
    bst.insert(12);
    bst.postorderTraversal();

    return 0;
}
