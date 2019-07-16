//
//  main.cpp
//  semantics_of_constructor
//
//  Created by SteveLin on 2019/7/16.
//  Copyright © 2019 unixlin. All rights reserved.
//

#include <iostream>
using namespace std;

class Foo {
public:
    int val;
    Foo *pnext;
public:
    Foo(){
        cout << __func__  << "  默认构造器被调用" << endl;
    };
    Foo(int a){
        val = a;
    }
    
};

class Bar {
public:
    Foo foo;
    char *name;
    Bar() {
        static char n[] = "static_unixlin";
        name = n;
    }
};

void foo_bar() {
    Bar bar;
    if (bar.name) {
        cout << bar.name << endl;
    }
}

int main(int argc, const char * argv[]) {
    foo_bar();
    return 0;
}
