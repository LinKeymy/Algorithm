//
//  DepthFirstPaths.cpp
//  graph_inderect
//
//  Created by SteveLin on 2019/8/16.
//  Copyright © 2019 SteveLin. All rights reserved.
//

//#include <iostream>
//#include <vector>

#include "Graph.cpp"
#include <stack>


class DepthFirstSearch {
protected:
    vector<bool> *v_marked;
    int m_count;
    
    // 对顶点 v 进行s search ， 并标记 v
    void dfs(const Graph & G, int v) {
        (*v_marked)[v] = true;
        ++m_count;
        for (int w : G.adjacent(v)) {
            if (!marked(w)) dfs(G, w);
        }
    }
    
public:
    // construction
    DepthFirstSearch(const Graph & G, int s) {
        v_marked = new vector<bool>(G.V(),false);
        m_count = 0;
        dfs(G, s);
    }
    
    DepthFirstSearch(const Graph & G) {
        v_marked = new vector<bool>(G.V(),false);
        m_count = 0;
    }
    ~DepthFirstSearch() {
        if (v_marked) {
            cout << "delete v_marked" << endl;
            delete v_marked;
        }
    }
    // 顶点 v 是否已经标记过
    bool marked(int v) {
        return (*v_marked)[v];
    }
    
    // 标记过的顶点的数量
    int count() {
        return m_count;
    }
    
};


// dsf 是先序遍历的推广 (dsf 生成棵搜索树)
class DepthFirstPaths: public DepthFirstSearch {
private:
    vector<int> *edgeTo;
    int s;
    
public:
    explicit DepthFirstPaths(const Graph & G, int s): DepthFirstSearch(G) {
        edgeTo = new vector<int>(G.V(),0);
        this->s = s;
        dsf(G, s);
    }
    
    ~DepthFirstPaths() {
        if (edgeTo) {
            cout << "delete edgeTo" << endl;
            delete edgeTo;
        }
    }
    
    // dsf 是先序遍历的推广 (dsf 生成棵搜索树)
    // 在递归过程就是压栈的过程，首先是s进入，然后s出栈，s出栈时将s的链接点入栈
    // 所以这里若不用递归，则可以使用一个栈的来while处理。
    void dsf(const Graph & G, int v) {
        (*v_marked)[v] = true;
        
        for (int w : G.adjacent(v)) {
            if (!marked(w)) {
                // 相当于搜索树中w的父亲节点是v
                (*edgeTo)[w] = v;
                dsf(G, w);
            }
        }
    }
    
    bool hasPathTo(int v) {
        return (*v_marked)[v];
    }
    
    stack<int>* pathTo(int v) {
        if (!hasPathTo(v)) return NULL;
        stack<int>* st = new stack<int>;
        for (; v != s; v = (*edgeTo)[v]) {
            st->push(v);
        }
        st->push(s);
        return st;
    }
    
    // todo: 打印搜索路径
    static void printPath(stack<int> & st) {
        cout << "Path: ";
        while (!st.empty()) {
            cout << st.top() << " -> ";
            st.pop();
        }
        cout << " null " << endl;
    }
};
