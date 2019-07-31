//
//  main.cpp
//  sum-of-two-integers
//
//  Created by SteveLin on 2019/7/30.
//  Copyright © 2019 SteveLin. All rights reserved.
//

#include <iostream>
using namespace std;

//class Solution {
//public:
//    int getSum(int a, int b) {
//        int c = 0;
//        while (b) {
//            c = (unsigned(a&b))<<1;
//            a = a^b;
//            b = c;
//        }
//        return a;
//    };
//};

//class Solution {
//public:
//    int getSum(int a, int b) {
//        while (b) {
//            auto c = ((unsigned int)a & b) << 1;
//            a = a ^ b;
//            b = c;
//        }
//        return a;
//    }
//};

//class Solution {
//public:
//    int getSum(int a, int b) {
//        if (b == 0) return a;
//        return getSum(a^b,((unsigned)a&b)<<1);
//    };
//};

class Solution {
public:
    int reverse(int x) {
        long res = 0;
        for (;x; res = res * 10 + (x % 10),x/=10);
        return (int)(res > 0x7fffffff || res < 0x80000000) ? 0 : (int)res;
    }
};

int main(int argc, const char * argv[]) {
    Solution s;
    s.reverse(123);
    return 0;
}
