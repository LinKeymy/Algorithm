//
//  main.cpp
//  o(logN)_pow
//
//  Created by SteveLin on 2019/7/9.
//  Copyright © 2019 alin. All rights reserved.
//

#include <iostream>


static int call_count = 0;

// 一个整数的幂(幂也是整数) o(logN)
long long pow(long long x, unsigned n) {
    call_count++;
    if (n == 0) {
        std::cout << "call_count = " << call_count << std::endl;
        call_count = 0;
        return 1;
    };
    if (n == 1) {
        std::cout << "call_count = " << call_count << std::endl;
        call_count = 0;
        return x;
    }
    bool isEven = n % 2 == 0;
    if (isEven) {
        return pow(x * x, n/2);
    } else {
        return pow(x * x, (n - 1) / 2) * x;
    }
    
}

int main(int argc, const char * argv[]) {
    pow(2, 45);
    return 0;
}
