//
//  main.cpp
//  sort
//
//  Created by SteveLin on 2019/7/28.
//  Copyright © 2019 SteveLin. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

void printV(vector<int>  & a) {
    for (auto it = a.begin(); it != a.end(); ++it) cout << *it << " ";
    cout << endl;
}

void insertionSort(vector<int> & a) {
    for (int i = 1; i < a.size(); ++i) {
        int tmp = move(a[i]);
        int j;
        for ( j = i; j > 0 && tmp < a[j - 1]; --j) {
            a[j] = move(a[j - 1]);
        }
        a[j] = move(tmp);
    }
    for (auto it = a.begin(); it != a.end(); ++it)
        cout << *it << " ";
}

void shellSort(vector<int> & a) {
    for (unsigned long gap = a.size() / 2; gap > 0 ; gap /= 2) {
        for (long i = gap; i < a.size(); i+=gap) {
            int tmp = move(a[i]);
            long j;
            for (j = i; j >= gap && tmp < a[j - gap]; j -= gap) {
                a[j] = move(a[j - gap]);
            }
            a[j] = tmp;
        }
    }
}

// 为了减少空间的使用，将每次从堆中移出的值转移到数组的后边，避免一个辅助数组的使用。
// 这样需要一个大小来控制这个删除过程的操作范围。【0，n）开区间
void percolateDown(vector<int> & a, long i, long n) {
    long child;
    for (; 2 * i + 1  < n; i = child) {
        child = 2 * i + 1;
        if ((child + 1) < n && a[child] < a[child + 1]) ++child;
        if (a[child] > a[i]) {
            swap(a[child], a[i]);
        } else {
            break;
        }
    }
}

void heapSort(vector<int> & a) {
    // 自下而上下滤建堆
    for (long i = a.size() / 2 - 1; i >= 0; --i) {
        percolateDown(a, i, a.size());
    }
    // 移除堆顶元素，将其放入数组未。
    for (long j = a.size() - 1; j > 0; --j) {
        swap(a[0], a[j]);
//        printV(a);
        percolateDown(a, 0, j);
        //        printV(a);
    }
     printV(a);
}

void merge_conquer(vector<int> & a, vector<int> tmp, long leftPos, long rightPos, long rightEnd) {
    long leftEnd = rightPos - 1;
    long mergePos = leftPos;  // 合并时，回移到a时的起始位置，结束位置还是rightEnd不会改变。
    long tmpPos = leftPos;
    
    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        if ( a[leftPos] <= a[rightPos]) {
            tmp[tmpPos++] = move(a[leftPos++]);
        } else {
            tmp[tmpPos++] = move(a[rightPos++]);
        }
        
        if (leftPos > leftEnd) {
            while (rightPos <= rightEnd) {
                tmp[tmpPos++] = move(a[rightPos++]);
            }
        }
        
        if (rightPos > rightEnd) {
            while (leftPos <= leftEnd) {
                tmp[tmpPos++] = move(a[leftPos++]);
            }
        }
    }
    
    // 将tmp移回a
    for (; mergePos <= rightEnd; ++mergePos) a[mergePos] = move(tmp[mergePos]);
}




void mergeSort(vector<int> & a, vector<int> & tmpArray, long left, long right) {
    if (left < right) {
        long center = (left + right) / 2;
        
        /*            分           */
        mergeSort(a, tmpArray, left, center);  // 左
        mergeSort(a, tmpArray, center + 1, right);  // 右
        
        /*            治           */
        merge_conquer(a, tmpArray, left, center + 1, right);
    }
}

void mergerSort(vector<int> & a) {
    vector<int> tmp(a.size());
    mergeSort(a, tmp, 0, a.size() - 1);
    printV(a);
}

vector<int> intersection(vector<int>& nums1, vector<int>& nums2) { sort(nums1.begin(),nums1.end());
    sort(nums2.begin(),nums2.end());
    int i=0,j=0; vector<int>
    res;
    while(i<nums1.size() && j<nums2.size()) {
        if(nums1[i]<nums2[j]) {
            i++;
        }
        else {
            if(nums1[i] == nums2[j] && (res.empty() || res.back() != nums1[i])) {
                res.push_back(nums1[i]);
            }
            j++;
            
        }
        
    }
    return res;
}

int binarySearch(vector<int>& nums, int target, int left, int right) {
    if (target > nums[right] || target < nums[left]) return -1;
    if (left == right) { return nums[left] == target ? left : -1; };
        int center = (left + right) / 2;
        if (nums[center] > target) {
            return binarySearch(nums, target, left, center - 1);
        } else if (nums[center] < target) {
            return binarySearch(nums, target, center + 1, right);
        } else {
            return center;
        }
    return -1;
};

int find_rotate_index(vector<int>& nums, int left, int right) {
    if (left == right - 1) return left;
    int center = (left + right) / 2;
    if (nums[left] > nums[center])
        return find_rotate_index(nums, left, center);
    else
        return find_rotate_index(nums, center, right);
};

//nums = [4,5,6,7,0,1,2], target = 0
class Solution {
public:
 
    int search(vector<int>& nums, int target) {
        if (nums.size() < 2) {
            for (int i = 0; i < nums.size(); ++i)
                if (nums[i] == target) return i;
            return -1;
        }
        int rotateIndex = find_rotate_index(nums, 0, (int)nums.size() -1);
        int index = binarySearch(nums, target, 0, rotateIndex);
        if (index != -1) return index;
        index = binarySearch(nums, target, rotateIndex + 1, (int)nums.size() - 1);
        return index;
    };
};


vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(),nums.end());
    for(int i = 0;i < nums.size() && nums[i] <= 0; i++) {
        if(i>0 && nums[i] == nums[i-1])
            continue;
        int lt = i+1; int rt = (int)nums.size() - 1;
        while(lt < rt) {
            int sums = nums[i] + nums[lt] + nums[rt];
            if( sums > 0 ) {
                --rt;
            }
            else if( sums < 0 ) {
                ++lt;
            } else {
                res.push_back({nums[i], nums[lt], nums[rt]});
                ++lt;
                while(lt < rt && nums[lt] == nums[lt-1] ) ++lt;
            }
        }
    }
    return res;
}

bool containsDuplicate(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    for (int i =  1; i < nums.size() ; ++i) {
        if (nums[i] == nums[i - 1]) return true;
    }
    return false;
}

string longestCommonPrefix(vector<string>& strs) {
    if (strs.size() == 1) return strs[0];
    string s = "";
    if (strs.size() > 1) {
        int i = 0;
        char c;
        string it = strs[0];
        while (it.size() > i) {
            c = it[i];
            for (int j = 1;j < strs.size(); ++j) {
                if (strs[j].size() <= i || strs[j][i] != c) return s;
                if (j == strs.size() - 1) s += c;
            }
            ++i;
        }
    }
    return s;
}


struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };

#include <queue>
int maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    int d = 0;
    queue<TreeNode* > st;
    st.push(root);
    int es = 1;
    while (!st.empty()) {
        TreeNode* top = st.front();
        st.pop();
        --es;
        if (top->right != nullptr) {
            st.push(top->right);
        }
        if (top->left != nullptr) {
            st.push(top->left);
        }
        if (es == 0) {
            es = (int)st.size();
            ++d;
        }
    }
    return d;
}

 struct ListNode {
         int val;
         ListNode *next;
         ListNode(int x) : val(x), next(NULL) {}
   };

#include <set>
//bool hasCycle(ListNode* head) {
//    if(NULL == head) return NULL;
//    set<ListNode*> st;
//    while (st.insert(head).second) {
//        if (head->next == nullptr) {
//            head = head->next;
//        }
//    }
//
//    return nullptr;
//}

ListNode *detectCycle(ListNode *head) {
    if(NULL == head) return NULL;
    set<ListNode*> st;
    while (st.insert(head).second) {
        if (head->next == nullptr) {
            return NULL;
        }
        head = head->next;
    }
    return head;
}


int maxSubArray(vector<int>& nums) {
    int tmp_sum = 0;
    int max_sum = INT_MIN;
    for (int i = 0; i < nums.size(); ++i) {
         tmp_sum += nums[i];
        if (tmp_sum > max_sum)
            max_sum = tmp_sum;
        else if (tmp_sum < 0)
            tmp_sum = 0;
    }
    return max_sum;
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* l3 = new ListNode(0);
    ListNode* res = l3;
    while (l1 != nullptr && l2 != nullptr ) {
        if (l1->val < l2->val) {
            l3->next = l1;
            l1 = l1->next;
            l3 = l3->next;
        } else {
            l3->next = l2;
            l2 = l2->next;
            l3 = l3->next;
        }
    }
    if (l1 != nullptr && l2 == nullptr) {
        l3->next = l1;
    } else if (l1 == nullptr && l2 != nullptr) {
        l3->next = l2;
    }
    return res->next;
}

int removeDuplicates(vector<int>& nums) {
    for (int i = 1; i < nums.size();) {
        if (nums[i] == nums[i-1]) {
            for (int j = i; j < nums.size() - 1; ++j) {
                nums[j] = move(nums[j + 1]);
            }
            nums.resize(nums.size() - 1);
        } else {
            ++i;
        }
    }
    return (int)nums.size();
}

/*
 
 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
* 解题思路：拆解
* 1、当有N层楼梯时，爬到（N-1）有X种方法，爬到（N-2）有Y种方法；
* 2、那么爬到N层的方法有（N-1） + （N-2）种；
*      （N-1）层，只能选择1，到第N层；
*      （N-2）层，只能选择2，到第N层；若选择一层一层上，该方法与（N-1）中重合；
* 3、故，F（N）= F（N-1）+ F（N-2）；
* 4、将其转换为：斐波那契数列问题；
* 5、注意优化；
*/


int climbStairs(int n) {
    if (n == 1) return 1;
    if (n == 2) return 2;
    int last = 1;
    int last2 = 2;
    int i = 3;
    while (i <= n) {
        last = last2 + last;
        swap(last2, last);
        ++i;
    }
    return last2;
};

/*
 给定两个有序整数数组 nums1 和 nums2，将 nums2 合并到 nums1 中，使得 num1 成为一个有序数组。
 
 说明:
 
 初始化 nums1 和 nums2 的元素数量分别为 m 和 n。
 你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
 示例:
 
 输入:
 nums1 = [1,2,3,0,0,0], m = 3
 nums2 = [2,5,6],       n = 3
 
 输出: [1,2,2,3,5,6]
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/merge-sorted-array
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    if (n == 0) return;
    nums1.reserve(m+n+1);
    int mK =  m + n;
    int i = m-1;
    for (; i >= 0; --i) {
        nums1[n+i] = move(nums1[i]);
    }
    i = 0;
    int j = 0;
    int k = n;
    while (j < n && k < mK) {
        if (nums2[j] < nums1[k]) {
            nums1[i] = move(nums2[j]);
            ++j;
        } else {
            nums1[i] = move(nums1[k]);
            ++k;
        }
        ++i;
    }
    while (j < n) {
        nums1[i] = move(nums2[j]);
        ++j;
        ++i;
    }
}


int removeElement(vector<int>& nums, int val) {
    int i = -1;
    for (int j = 0; j < nums.size(); ++j) {
        if (val != nums[j]) {
            if (j - i > 1) {
                nums[i + 1] = move(nums[j]);
            }
            ++i;
        }
    }
    return i+1;
}

class MinStack {
    struct MinStackE {
        int val;
        int stackIndex;
        MinStackE(int v, int i = 0):val{v},stackIndex{i} {};
        MinStackE(const MinStackE & e){
            this->val = e.val;
            this->stackIndex = e.stackIndex;
        };
        
    };
    vector<MinStackE *> nums;
    int currentSize = 0;
    
    void percolateDown(int hole) {
        MinStackE *tmp = nums[hole];
        int c = hole * 2;
        for (; c < currentSize;) {
            if (c < currentSize && nums[c]->val > nums[c+1]->val) ++c;
            if (nums[c]->val < nums[hole]->val) {
                nums[hole] = nums[c];
                hole = c;
                c = hole * 2;
            } else {
                break;
            }
        }
        nums[hole] = tmp;
    }
    
    void percolateUp(int val) {
        
        MinStackE *tmp = new MinStackE(val);
        if (currentSize == nums.size() - 1) {
            nums.resize(2 * nums.size());
        }
        int hole = ++currentSize;
        nums[0] = tmp; // 当 hole / 2 == 0 时 跳出
        for (; val < nums[hole / 2]->val; hole /= 2 ) {
            nums[hole] = nums[hole / 2];
        }
        nums[hole] = tmp;
    }
    
    
    
    
public:
    /** initialize your data structure here. */
    
    MinStack() {
        nums.reserve(20);
        nums.push_back(0);
    }
    
    void push(int x) {
        for (int i = 1; i <= currentSize; ++i) {
            ++nums[i]->stackIndex;
        }
        percolateUp(x);
    }
    
    void pop() {
        if (currentSize == 0) return;
        
        
        int top_Index = 1;
        for (int i = 1; i <= currentSize; ++i) {
            if (nums[i]->stackIndex == 0) { top_Index = i; };
            --nums[i]->stackIndex;
        }
        
        nums[top_Index] = nums[currentSize--];
        percolateDown(top_Index);
    }
    
    int top() {
        if (currentSize == 0) return INT_MIN;
        for (int i = 1; i <= currentSize; ++i) {
            if (nums[i]->stackIndex == 0) {
                return nums[i]->val;
            }
        }
        return INT_MIN;
    }
    
    int getMin() {
        if (currentSize == 0) return INT_MIN;
        return nums[1]->val;
    }
};

int searchInsert(vector<int>& nums, int lt, int rt, int target) {
    if (lt >= rt) return lt;
    int center = (lt + rt) / 2;
    if (target > nums[center]) {
        return searchInsert(nums,center + 1, rt, target);
    } else if (target < nums[center]) {
        return searchInsert(nums,lt, center, target);
    } else {
        return center;
    }
}




int searchInsert(vector<int>& nums, int target) {
    int lt = 0;
    int rt = (int)nums.size() - 1;
    while (rt > lt) {
        int center = (lt + rt) / 2;
        if (target < nums[center]) {
            rt = --center;
        }
        else if (nums[center] < target) {
            lt = ++center;
        } else {
            return center;
        }
    }
    return lt;
}


bool isPalindrome(int x) {
    if (x < 0) return false;
    unsigned int res = 0;
    unsigned int ret = x;
    while (ret > 10) {
        res = (res + ret % 10) * 10;
        ret /= 10;
    }
    return res == x;
}

int singleNumber(vector<int>& nums) {
    if (nums.size() == 1) return nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        nums[0] ^= nums[i];
    }
    return nums[0];
}


int main(int argc, const char * argv[]) {
    
    
    MinStack *minStack = new MinStack();
    minStack->push(-2);
    minStack->push(0);
    minStack->push(-1);
    cout << minStack->getMin() << endl;
    cout << minStack->top() << endl;
    minStack->pop();
    cout << minStack->top() << endl;
    cout << minStack->getMin() << endl;
    minStack->push(-5);
    minStack->push(-1);
    
    cout << minStack->top() << endl;
    cout << minStack->getMin() << endl;

    vector<int> nums11 = {1,2,4,5,6,0};
    vector<int> nums22 = {3};
    nums11.reserve(nums11.size() + nums22.size() + 1);
    merge(nums11,5,nums22,1);
    
    
    vector<int> nums = {1};
    vector<int> nums1 = {1,1,2,2,3,3,3,3};
    vector<int> nums2 = {3,3,3,3};
    vector<int> num3 = {};
    
    removeDuplicates(nums);
     removeDuplicates(nums1);
     removeDuplicates(nums2);
     removeDuplicates(num3);
    
   // 1->2->4, 1->3->4
    ListNode *l11 = new ListNode(1);
    ListNode *l12 = new ListNode(3);
    ListNode *l13 = new ListNode(4);
    l11->next = l12;
    l12->next = l13;
    
    ListNode *l21 = new ListNode(1);
    ListNode *l22 = new ListNode(2);
    ListNode *l23 = new ListNode(4);
    
    l21->next = l22;
    l22->next = l23;
    
    ListNode *l = mergeTwoLists(l11, l21);
    while (l != nullptr) {
        cout << l->val << " -> ";
        l = l->next;
    }
    cout << endl;
    return 0;
}
