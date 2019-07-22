//
//  main.cpp
//  stack_balance_symbol
//
//  Created by SteveLin on 2019/7/17.
//  Copyright © 2019 unixlin. All rights reserved.
//

#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    static bool isOPend(const char & c) {
        return c == '(' | c == '[' | c == '{';
    }
    
   static bool cmp(const char & c1, const char & c2) {
        if (c1 == '(') return c2 == ')';
        if (c1 == '[') return c2 == ']';
        if (c1 == '{') return c2 == '}';
        return false;
    }
    
    static bool isValid(string s) {

        stack<char> st;
        auto length = s.length();
        
        // 长度为奇数，false
        if (length % 2) return false;
        
        for (int i = 0; i < length; ++i) {
            char c = s[i];
            if (isOPend(c)) {  // 开放符号 入栈
                st.push(c);
            } else {
                if (st.empty()) return false;  // 如果是闭符号，empty
                if (cmp(st.top(), c)) { // 如果匹配的
                    st.pop();
                } else { // 如果发现不匹配 false
                    return false;
                }
            }
        }
        return st.empty();
    }
};

int main(int argc, const char * argv[]) {
    string s = "((((((";
    cout << Solution::isValid(s) << endl;
    return 0;
}
