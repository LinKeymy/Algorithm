//
//  main.cpp
//  148
//
//  Created by SteveLin on 2019/8/4.
//  Copyright © 2019 SteveLin. All rights reserved.
//

#include <iostream>

/*
 在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。
 输出: 4->2->1->3
 输出: 1->2->3->4
 */

#include <vector>



struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummyHead(0);
        ListNode *p = &dummyHead; // 这样的赋值是拷贝构造p，不是所要的让P指h
        while (l1 != NULL && l2 != NULL) {
            if (l1->val < l2->val) {
                p->next = l1;
                l1 = l1->next;
            } else {
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        if (l1 != NULL) {
            p->next = l1;
        }
        if (l2 != NULL) {
            p->next = l2;
        }
        return dummyHead.next;
    }
    
    ListNode *cut(ListNode* l, int length) {
        ListNode *tmp = l;
        // 这样的做法不OK，需要将cut后的链完全断开，不仅仅是返回头部，
        // 不然外部无法知到断开的链的尾部，也就是断开是真的断开，被cut的每个字链都有尾 ->NULL
//        while ( 0 == length--) {
//            tmp = tmp->next;
//        }
        while (--length != 0 && tmp != NULL) {
            tmp = tmp->next;
        }
        if (tmp == NULL) return NULL;  // length 需要cut的长度比链要长
        l = tmp->next;    // 右边剩下的头
        tmp->next = NULL; // cut 下的尾
        return l;
    }
    
    ListNode* sortList(ListNode* head) {
        int length = 0;
        ListNode dummy(0);
        dummy.next = head;
        ListNode *tmp = head;
        
        while (tmp != NULL) {
            ++length;
            tmp = tmp->next;
        }
        
        for (int size = 1; size < length; size *= 2) {
            ListNode *current = dummy.next;  // 要归并的链
            ListNode *tail = &dummy;  //  已经归并链的接入点
            while (current != NULL) {
                // 1 2 3 4 5
                // lp->1;
                ListNode *lp = current;
                // rp->2;
                ListNode *rp = cut(lp, size);
                // current->3
                current = cut(rp, size);
                // 将lp 、 rp 排序并返回
                tail->next = merge(lp, rp);
                while (tail->next != NULL) {  // 每次将merge结果接入链后，tail指向链的尾部
                    tail = tail->next;
                }
            }
        }
        return dummy.next;
    }
};

ListNode *list(int *a, int n) {
    ListNode *list = NULL;
    ListNode *tmp = NULL;
    for (int i = 0; i < n; ++i) {
        if (tmp == NULL) {
              tmp = new ListNode(a[i]);
        } else {
            tmp->next = new ListNode(a[i]);
            tmp = tmp->next;
        }
        if (list == NULL) {
            list = tmp;
        }
    }
    return list;
}

int main(int argc, const char * argv[]) {
    int a[5] = {1,5,3,4,0};
    ListNode *l = list(a, 5);
    Solution s;
    l = s.sortList(l);
    return 0;
}
