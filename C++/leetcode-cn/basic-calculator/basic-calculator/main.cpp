//
//  main.cpp
//  basic-calculator
//
//  Created by SteveLin on 2019/7/17.
//  Copyright © 2019 unixlin. All rights reserved.
//

#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

/*

 */


class Solution_0 {
private:
    stack<int> num;
    stack<char> op;
    int pri(char a){
        switch(a){
            case '+': return 1;
            case '-': return 1;
            case '*': return 2;
            case '/': return 2;
            case '(': return 3;
            default: return -1;
        }
    }
    void cal(){
        int b=num.top();num.pop();
        int a=num.top();num.pop();
        switch(op.top()){
            case '+':num.push(a+b);break;
            case '-':num.push(a-b);break;
            case '*':num.push(a*b);break;
            case '/':num.push(a/b);break;
        }
        op.pop();
    }
public:
    int calculate(string s) {
        string ss;
        for(int i=0;i<(int)s.size();i++){
            if(isdigit(s[i]))
                ss+=s[i]; // 它可能是多位的数字 100908....
            else if(s[i]==' ') continue;
            else{
                if(!ss.empty()){ // 前面读出的操作数，输出
                    num.push(stoi(ss));
                    ss.clear();
                }
                
                if(op.empty()||s[i]=='('|| pri(op.top())<pri(s[i]) ) { // 优先级比栈顶直接入栈
                    op.push(s[i]);
                } else if(s[i]==')') {
                    while(op.top()!='(') cal();
                    op.pop();  // 这个pop是对 ‘（’ 的动作
                } else {
                    // 优先级低，先等栈高优先级运算完成后入栈
                    while(!op.empty()&&pri(op.top())<=pri(s[i])) cal();
                    op.push(s[i]);
                }
            }
        }
        // 最后一位，可能是数，它在上面的for中没有被录入
        if(!ss.empty()) num.push(stoi(ss));
        while(!op.empty()) cal();
        return num.top();
    }
};


class Solution {
    
public:
    static int calculate(string s) {
        // 统计遇到 -（ 的情况
        stack<bool> sign;
        
        int minus = 1;
        int sum = 0;
        int currentOp = 1; // -1 1
        string ss; // 操作数字符
        char si;
        for(int i=0;i<(int)s.size();i++){
            si = s[i];
            if(isdigit(si)) {
                ss+=si;
            } else if (si==' ') continue;
            else {
                if (!ss.empty()) {
                    sum += (minus * currentOp * stoi(ss));
                    ss.clear();
                }
                if (si == '-') {
                    currentOp = -1;
                } else if (si == '+') {
                    currentOp = 1;
                } else if (si == '(') {
                     sign.push(currentOp == -1);
                    if (currentOp == -1) {
                        minus = -minus;
                        currentOp = 1;
                    }
                } else if (si == ')') {
                    if (sign.top())  minus = -minus;
                      sign.pop();
                } else {
                    cout << "undefined symbol";
                }
            }
          }
        if (!ss.empty()) (sum += (minus * currentOp * stoi(ss)));
        return sum;
    }
};



int main(int argc, const char * argv[]) {
    cout << Solution::calculate("1-(5)") << endl;
    return 0;
}
