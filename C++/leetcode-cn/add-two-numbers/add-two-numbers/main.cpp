//
//  main.cpp
//  add-two-numbers
//
//  Created by SteveLin on 2019/7/30.
//  Copyright © 2019 SteveLin. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class list {
public:
    
    list() {
        root = nullptr;
    }
    
    void insert(ListNode & node) {
        ListNode *n = new ListNode(node.val);
        if (root == nullptr) {  root = n; return;};
         ListNode *pn = root;
        while (pn->next != nullptr) {
            pn = pn->next;
        }
        pn->next = n;
    }

    void insert(ListNode && node) {
        ListNode *n = new ListNode(node.val);
        if (root == nullptr) {  root = n; return;};
        ListNode *pn = root;
        while (pn->next != nullptr) {
            pn = pn->next;
        }
        pn->next = n;
    }
    ListNode *root;
};
//
class Solution1 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        vector<int> v;
        v.push_back(0);
        ListNode *node1 = l1;
        ListNode *node2 = l2;
        while (node1 != nullptr && node2 != nullptr) {
            int sum = node2->val + node1->val + v.back();
            v.pop_back();
            if (sum > 9) {
                v.push_back(sum % 10);
                v.push_back(1);
            } else {
                v.push_back(sum);
                v.push_back(0);
            }
            node2 = node2->next;
            node1 = node1->next;
        }
        
        node1 = node2 == nullptr ? node1 : node2;
        while (node1 != nullptr) {
            int sum = node1->val + v.back();
            v.pop_back();
            if (sum > 9) {
                v.push_back(sum % 10);
                v.push_back(1);
            } else {
                v.push_back(sum);
                v.push_back(0);
            }
            node1 = node1->next;
        }
        
        int sum = 0;
        for (int i = 0; i < v.size(); ++ i) {
            sum += v[i] * pow(10, i);
        }
        l1->val = sum;
        return l1;
    };
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *mirror = l1;
        while (l2 != nullptr) {
            l1->val += l2->val;
            if (l1->next == nullptr && l2->next != nullptr) {
                l1->next = l2->next;
                l2 = nullptr;
            } else {
                l1 = l1->next;
                l2 = l2->next;
            }
        }
        l1 = mirror;
        while (l1 != nullptr) {
            if (l1->val > 9) {
                l1->val = l1->val % 10;
                if (l1->next != nullptr) {
                    ++ (l1->next->val);
                } else {
                    l1->next = new ListNode(1);
                }
            }
            l1 = l1->next;
        }
        return mirror;
    };
};

int main(int argc, const char * argv[]) {
    list l1;
    l1.insert(ListNode(2));
    l1.insert(ListNode(4));
    l1.insert(ListNode(3));
    list l2;
    l2.insert(ListNode(5));
    l2.insert(ListNode(6));
    l2.insert(ListNode(4));
    Solution s;
    
    cout << s.addTwoNumbers(l1.root, l2.root)->val << endl;

    return 0;
}
