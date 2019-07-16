//
//  main.cpp
//  vector
//
//  Created by SteveLin on 2019/7/14.
//  Copyright © 2019 unixlin. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
void print(const string& name) {
    cout << "c_value detected:" << name << endl;
}

void print(string& name) {
    cout << "lvalue detected:" << name << endl;
}


void print(string&& name) {
    cout << "rvalue detected:" << name << endl;
}

class System {
    
public:
    string *name;
    
public:
    // constuctor
    System (const char chars[]){
         cout << "constuctor from " << chars << endl;
        name = new string(chars);
    }
    
    // copy constructor
    System (const System &system){
        cout << "copy from " << *(system.name) << endl;
        name = new string(system.name->c_str());
    }
    
    // copy assign
    System& operator= (const System& rsystem) {
        cout << "assign from " << *(rsystem.name) << endl;
        System tmp(rsystem.name->c_str());
        string *s = this->name;
        this->name = tmp.name;
        tmp.name = s;
        return *this; // 取的this指向的变量，返回给外部引用
    }
    
    // move assign
    System& operator= (System&& rsystem) {
        cout << "System& operator= (System&& rsystem)" << endl;
        this->name = rsystem.name; // 使用了rsystem的name，无需深拷贝
        // rsystem 本身很快就销毁，这里因为已经被this->name指向了，
        // 就设为NULL，防止rsystem销毁时被delete
        rsystem.name = NULL;
        return *this; // 取的this指向的变量，返回给外部引用
    }
        
        // move constructor
        System(System&& rsystem) {
        cout << "System(System&& rsystem" << endl;
        this->name = rsystem.name; // 使用了rsystem的name，无需深拷贝
        // rsystem 本身很快就销毁，这里因为已经被this->name指向了，
        // 就设为NULL，防止rsystem销毁时被delete
        rsystem.name = NULL;
        }
//
    // destructor
    ~System() {
        if (name) {
            cout << "destructor of " << *name << endl;
            delete name;
        }
    }
};

void copy() {
    cout << "- - - - - - - - - - copy start - - - - - - - - - " << endl;
    System xos("xos");
    System xos_1 = xos;
    cout << "- - - - - - - - - - copy end - - - - - - - - - " << endl;
}

void assign() {
    cout << "- - - - - - - - - - assign start - - - - - - - - - " << endl;
    System xos("xos");
    System windows("window");
    windows = xos;  // operator=
    cout << "- - - - - - - - - - assign end - - - - - - - - - " << endl;
}

void rvalue() {
    cout << "- - - - - - - - - - rvalue start - - - - - - - - - " << endl;
    System windows("window");
    windows = System("xos");
        System windows1 = System("windows1");
        System window1(windows);
        cout << windows1.name->c_str() << endl;
    cout << "- - - - - - - - - - rvalue end - - - - - - - - - " << endl;
}
        

void printMoveConstructor( System &&rhs) {
    System s = System(rhs);
        string *b = std::move(rhs.name);
   cout << "printMoveConstructor: " << b->c_str() << endl;
}

class MyString {
private:
    char* _data;
    size_t   _len;
    void _init_data(const char *s) {
        _data = new char[_len+1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }
public:
    MyString() {
        _data = NULL;
        _len = 0;
    }
    
    MyString(const char* p) {
        
        _len = strlen (p);
        _init_data(p);
        std::cout << "Base Constructor is called! source: " << this->_data << std::endl;
    }
    
    MyString(const MyString& str) {
        _len = str._len;
        _init_data(str._data);
        std::cout << "Copy Constructor is called! source: " << str._data << std::endl;
    }
    
    MyString& operator=(const MyString& str) {
        if (this != &str) {
            _len = str._len;
            _init_data(str._data);
        }
        std::cout << "Copy Assignment is called! source: " << str._data << std::endl;
        return *this;
    }
    
    virtual ~MyString() {
        if (_data) free(_data);
    }
    
    MyString(MyString&& str) {
        std::cout << "Move Constructor is called! source: " << str._data << std::endl;
        _len = str._len;
        _data = str._data;
        str._len = 0;
        str._data = NULL;
    }
    
    MyString& operator=(MyString&& str) {
        std::cout << "Move Assignment is called! source: " << str._data << std::endl;
        if (this != &str) {
            _len = str._len;
            _data = str._data;
            str._len = 0;
            str._data = NULL;
        }
        return *this;
    }

};

//int main() {
//    MyString a;
//    a = MyString("Hello");
//    std::vector<MyString> vec;
//    vec.push_back(MyString("World"));
//}
//
int main(int argc, const char * argv[]) {
    
//    printMoveConstructor(System("hhh"));
    System sss("d");
    System d = System("d");   // constructor
    System s = System("s");   // constructor
    s = d; // copy assign
    System n = d; // copy constructor
    System t = std::move(d);  // move constructor
    s = System("ss"); // move assign
    s = std::move(d); // move assgn
    return 0;
}
