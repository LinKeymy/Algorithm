//
//  main.cpp
//  hash_function
//
//  Created by SteveLin on 2019/7/24.
//  Copyright © 2019 unixlin. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Person {
    string m_name;
    int m_age;
};
template <typename Object>
class HashTable {
    static const int TABLE_SIZE = 1016;
    vector<Object * > v;
public:
    HashTable() {
        v = vector<Object *> (TABLE_SIZE);
    };
private:
    int hash(const string & key, int tableSize) const {
        int hashVal = 0;
        for(char ch: key) {
            hashVal += ch;
        }
        return hashVal;
    }
public:
    Object & operator[](const string & key) {
        return *v[this->hash(key, TABLE_SIZE)];
    };
    
    const Object & operator[](const string & key) const{
        return *v[this->hash(key, TABLE_SIZE)];
    };
    
};


int main(int argc, const char * argv[]) {
    
    HashTable<Person> table;
    Person p1;
    p1.m_name = "alin";
    p1.m_age = 100;
    table[p1.m_name] = p1;
    
    return 0;
}
