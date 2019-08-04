//
//  main.cpp
//  reverse-linked-list
//
//  Created by SteveLin on 2019/7/31.
//  Copyright © 2019 SteveLin. All rights reserved.
//

// reverse-linked-list
#include <iostream>
#include <vector>
// https://leetcode-cn.com/problems/reverse-linked-list/

using namespace std;
  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };


ListNode* reverseList(ListNode* head) {
    ListNode *p;
    for(p=NULL; head; swap(head,p))
        // 每次进行wap(p,head->next)时，将head->next指针指向p之前🈯️的内容
        // 1 -> 2 -> 3 -> 4   , -> 表示指向
        // 假设 p -> 1 , h->2 , h.next -> 3
        // swap(p,head->next); => p-> 3, h->2, h.next -> 1
        swap(p,head->next);
    return p;
}

//  1->2->3->4->5->NULL, m = 2, n = 4  , 1 ≤ m ≤ n ≤ 链表长度。
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode *p = nullptr;
        ListNode *s = nullptr;
        ListNode *start = head;
        for ( int i = 1; i <= n ; ++i) {
            if (i <= m) {
                s = p;
                p = head;
                head = head->next;
            } else if ( i > m && i <=n) {
                swap(p, head->next);
                swap(head, p);
            }
        }
        
        if (m == 1) { start->next = head; }
        else { s->next->next = head;  s->next = p; }
        if (m == 1) return p;
        return start;
    }

ListNode* rotateRight(ListNode* head, int k) {
    vector<ListNode* > v;
    while (head != nullptr) {
        v.push_back(head);
        head = head->next;
    }
    int r = k % v.size();
    if (r > 0) {
        v[v.size() - 1]->next = v[0];
        v[v.size() - r - 1]->next = nullptr;
        return v[v.size() - r];
    }
    return v[0];
}

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        vector<ListNode *> v;
        while (head != nullptr) {
            v.push_back(head);
            head = head->next;
        }
        for (long i = v.size() - 1; i > 0; --i) {
                v[i]->next = v[i-1];
        }
        return head;
    };
};

int main(int argc, const char * argv[]) {
    ListNode *tmp = nullptr;
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    tmp = head->next;
    tmp->next = new ListNode(3);
    tmp = tmp->next;
    tmp->next = new ListNode(4);
    tmp = tmp->next;
    tmp->next = new ListNode(5);
    head = rotateRight(head,6);
    return 0;
}
