//
//  main.cpp
//  max_sub_sum
//
//  Created by SteveLin on 2019/7/8.
//  Copyright © 2019 alin. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;


/*
 设 i = 5， j = 7
 j =  5     6    7      .....
 k =  5    5 6  5 6 7
 所以 for (int k = i; i <= j; ++k)
 
 O(N^3)
 */
int max_sub_sum_1(const vector<int> &vec) {
    int max_sum = 0;
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = i; j < vec.size(); ++j) {
            int thisSum = 0;
            for (int k = i; k <= j; ++k) {
                thisSum += vec[k];
            }
            if (thisSum > max_sum) {
                max_sum = thisSum;
            }
        }
    }
    return max_sum;
}


/*
 设  i = 5，  j = 7
    j =  5      6      7      .....
  sum =  5    5 + 6  5 + 6 +7
 j的后面的一项的和等于前面求得的；j = 7 时 为 (5 + 6) + 7
  O(N^2)
 */
int max_sub_sum_2(const vector<int> &vec){
    int max_sum = 0;
    for (int i = 0; i < vec.size(); ++i) {
        int thisSum = 0;
        for (int j = i; j < vec.size(); ++j) {
            thisSum += vec[j];
            // 重复了前面的求和过程
//            for (int k = i; k <= j; ++k) {
//                thisSum += vec[k];
//            }
            if (thisSum > max_sum) {
                max_sum = thisSum;
            }
        }
    }
    return max_sum;
}

/*
 最大子序列的递归算法
 */
// 求三个数的最大值
int max3_int(int a, int b, int c) {
    int max_ab = max(a, b);
    return max(max_ab,c);
}

int maxSubRec(const vector<int> &vec,int left, int right) {
    if (left == right) {
        if (vec[left] > 0) {
            return vec[left];
        } else {
            return 0;
        }
    }
    
    int center = (left + right) / 2;
    int sum_leftRec = maxSubRec(vec, left, center);
    int sum_rightRec = maxSubRec(vec, center + 1, right);
    
     // 左边部分的最大子序列
    int leftBorderSum = 0, max_leftBorderSum = 0;
    for (int i = center; i >= left; --i) {
        leftBorderSum += vec[i];
        if (leftBorderSum > max_leftBorderSum) {
            max_leftBorderSum = leftBorderSum;
        }
    };
    
    // 右边部分的最大子序列
    int rightBorderSum = 0, max_rightBorderSum = 0;
    for (int j = center + 1; j <= right; ++j) {
        rightBorderSum += vec[j];
        if (rightBorderSum > max_rightBorderSum) {
            max_rightBorderSum = rightBorderSum;
        }
    };
    
    int max_centerBorderSum = max_rightBorderSum + max_leftBorderSum;
    // 返回前、中、后三个部分中最大的部分。
    return max3_int(sum_leftRec, sum_rightRec, max_centerBorderSum);
};

/*
 o(N(logN)
 */
int max_sub_sum_3(const vector<int> &vec) {
    return maxSubRec(vec, 0, (int)vec.size() - 1);
}


/*
 O(N)
 */

int max_sub_sum_4(const vector<int> &vec) {
    int thisSum = 0, max_sum = 0;
    for (int i = 0; i < vec.size(); ++i) {
        thisSum += vec[i];
        if (thisSum > max_sum) {
            max_sum = thisSum;
        } else if (thisSum < 0) {
            thisSum = 0;
        }
    }
    return max_sum;
}


int main(int argc, const char * argv[]) {
    int count = 3000;
    int a = - 10000;
    int b = 10000;
    
    vector<int> vec(count);
    for (int i = 0; i < count; i++) {
        int v = (rand() % (b-a+1))+ a;
        vec[i] = v;
    }
    int max_2 = max_sub_sum_2(vec);
    cout << "max_sub_sum_2 = " << max_2 << endl;
    int max_3 = max_sub_sum_3(vec);
    cout << "max_sub_sum_3 = " << max_3 << endl;
    int max_1 = max_sub_sum_1(vec);
    cout << "max_sub_sum_1 = " << max_1 << endl;
    int max_4 = max_sub_sum_1(vec);
    cout << "max_sub_sum_4 = " << max_4 << endl;
    
    return 0;
}
