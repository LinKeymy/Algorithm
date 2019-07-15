//
//  main.cpp
//  vector
//
//  Created by SteveLin on 2019/7/14.
//  Copyright © 2019 unixlin. All rights reserved.
//

#include <iostream>
#include "Vector.cpp"
#include <vector>

using namespace std;


template <typename Element>
void move_vector(Vecter<Element> &&vec) {
    // 如果在函数内部右使用的话，就会调用  Vecter 的 move assignment
    Vecter<int> vec1 = std::move(vec);
    
    cout << "vec.begin =" << *vec1.begin() << ",  vec.back = " << *(vec1.end()-1) << endl;
}


int main(int argc, const char * argv[]) {
    
    Vecter<int> vec(10);
    vec.push_back(2);
    int a = 10;
    vec.push_back(a);
    a = 100;
    // 直接 使用 move 语句，就会调用 move construct; 对应于左值引用的copy constructor
    Vecter<int> vec1 = std::move(vec);
    //
    Vecter<int> vec2 = Vecter<int>(20);
    vec1 = Vecter<int>(20);
    move_vector(Vecter<int>());
//    cout << "a = " << a << ",  vec.back = " << *(vec.end()-1) << endl;
    return 0;
}
