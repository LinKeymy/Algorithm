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





int main(int argc, const char * argv[]) {
//    vector<int> v = {81,94,11,96,12,35,17,95,28,58,41,75,15};
    
    vector<int> v = {1,8};
    vector<int> v_copy = {81,94,11,96,12,35,17,95,28,58,41,75,15};
    
    vector<int> v1 = {1,9,2,10,3,11,4,12,5,13,6,14,7,15,8,16};
    vector<int> v_p = {97,53,59,26,41,58,31};
//    heapSort(v);
//    heapSort(v1);
//    mergerSort(v_copy);
    Solution s;
    cout << s.search(v,8) << endl;

//    shellSort(v);
//    shellSort(v1);
    return 0;
}
