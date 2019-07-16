//
//  main.cpp
//  linkList
//
//  Created by SteveLin on 2019/7/16.
//  Copyright © 2019 unixlin. All rights reserved.
//

#include <iostream>
#include "List.cpp"

int main(int argc, const char * argv[]) {
    
    List<int> list{};
    int a = 10;
    int b = 20;
    list.push_front(12);
    list.push_back(24);
    list.push_front(a);
    list.push_back(b);

    return 0;
}
