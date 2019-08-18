//
//  main.cpp
//  Digraph
//
//  Created by SteveLin on 2019/8/16.
//  Copyright © 2019 SteveLin. All rights reserved.
//

#include <iostream>
#include "Digraph.hpp"
#include <fstream>
#include <queue>
#include <stack>

void test_giraph() {
    ifstream fin("tinyDG.txt");
    Digraph dG(fin);
    dG.print();
    Digraph rdg = dG.reverse();
    rdg.print();
}


class DirectedDFS {
    vector<bool> v_marked;
public:
    DirectedDFS(const Digraph & dig, int v) {
        v_marked = vector<bool>(dig.v(),false);
        dfs(dig, v);
    }
    
    DirectedDFS(const Digraph & dig, vector<int> ves ) {
        v_marked = vector<bool>(dig.v(),false);
        dfs(dig, ves);
    }
    
    void print() {
        cout << "vertexs: 1" << endl;
        cout << "to vertexs: ";
        for (int v = 0; v < v_marked.size(); ++v) {
            int m = v_marked[v];
            if (m == true) {
                cout << " " << v;
            }
        }
        cout << endl;
    }
    
    bool marked(int v) {
        return v_marked[v];
    }
    
    // 单点可达
    void dfs(const Digraph & dig, int v) {
        v_marked[v] = true;
        for (int w : dig.adjacent(v))
            if(!marked(w))
                dfs(dig, w);
    }
    
    // 多点可达
    void dfs(const Digraph & dig, vector<int> ves ) {
        for (int w : ves)
            if (!marked(w)) // 如果 w marked 那么根据递归的性质，通过它的可达点都会marked
                 dfs(dig, w);
    }
};


class DirectedCycle {
private:
    vector<bool> v_marked;
    vector<int> v_edgeTo;
    stack<int> st_cycle;
    vector<bool> onStack;
    bool m_hasCycle = false;
    
public:
    
    DirectedCycle(const Digraph & G) {
        onStack = vector<bool>(G.v());
        v_marked = vector<bool>(G.v());
        v_edgeTo = vector<int>(G.v());
        for (int v = 0; v < G.v(); ++v)
             if (!v_marked[v])
                 dfs(G, v);
    }
    
    void dfs(const Digraph & G, int v) {
        onStack[v] = true;
        v_marked[v] = true;
        for (int w : G.adjacent(v)) {
            if (hasCycle()) { // 这个return是for循环中，检查之前某个w路径可能找到了环。停止检查。
                return;
            }
            else if (!v_marked[w]) {
                v_edgeTo[w] = v;
                dfs(G, w);
            // onStack[w] 在当前搜索树的路径上(递归栈中)被marked过，
            // 根据性质 w->..... ->v（w到v有路径可达）,而且也满足v->w
            // v_marked[w] 有可能是之前其他路径的入度访问的， onStack[w] 保障是当前递归的路径
            } else if (onStack[w]) {
                st_cycle = stack<int>{};
                m_hasCycle = true;
                for (int x = v; x != w; x = v_edgeTo[x]) { // 追溯回到 W 点
                    st_cycle.push(x);
                }
                st_cycle.push(w);
                st_cycle.push(v); // for循环从 v 开始（x = v），然后这里 v 结束，表示一个环。
            }
        }
        // for结束后，在返回前让 v 出栈，此时递归深入过程结束，属于return过程。
        onStack[v] = false;
    }
    
    bool hasCycle() {
        return m_hasCycle;
    }
    
    stack<int> cycle() {
        return st_cycle;
    }
};


class DepthFirstOrder {
private:
    vector<bool> v_marked;
    queue<int> q_pre;
    queue<int> q_post;
    stack<int> st_reversePost;
    bool marked(int v) {
        return v_marked[v];
    }
    
    
public:
    
    DepthFirstOrder(const Digraph & G) {
        v_marked = vector<bool>(G.v(),false);
        q_pre = queue<int>{};
        q_post = queue<int>{};
        st_reversePost = stack<int>{};
        for (int v = 0; v < G.v(); ++v)
            if (!marked(v))
                dfs(G, v);
    }
    
    void dfs(const Digraph & G, int v) {
        q_pre.push(v);
        v_marked[v] = true;
        for (int w : G.adjacent(v))
            if (!marked(w))
                dfs(G, w);
        q_post.push(v);
        st_reversePost.push(v);
    }
    
    queue<int> pre() {
        return q_pre;
    }
    
    queue<int> post() {
        return q_post;
    }
    
    stack<int> reversePost() {
        return st_reversePost;
    }
};


// 计算强连通分量的kosaraju算法
class SCC {
    
private:
    vector<bool> v_marked;
    vector<int> scc_id;
    int scc_count = 0;
    
public:
    
    SCC(const Digraph & G) {
        v_marked = vector<bool>(G.v(),false);
        scc_id = vector<int>(G.v());
        Digraph Gr = G.reverse();
        DepthFirstOrder order(Gr);
        stack<int> st = order.reversePost();
        while (!st.empty()) {
            int v = st.top();
            st.pop();
            if (!marked(v)) {
                dfs(G, v);
                ++scc_count;
            }
        }
    }
    
    void dfs(const Digraph & G, int v) {
        v_marked[v] = true;
        scc_id[v] = scc_count;
        for (int w : G.adjacent(v))
            if (!marked(w))
                dfs(G, w);
    }
  
    bool marked(int v) {
        return v_marked[v];
    }
    bool stronglyConnected(int v, int w) {
        return scc_id[v] = scc_id[w];
    }
    
    int id(int v) {
        return scc_id[v];
    }
    
    int count() {
        return scc_count + 1;
    };
    
    void print() {
        cout <<  this->count() << "  components" << endl;
        for (int i = 0; i < this->count(); ++i) {
            for (int w : this->cc(i)) {
                cout << " " << w;
            }
            cout << endl;
        }
    }
    
    vector<int> cc(int m_id) {
        vector<int> c;
        for (int i = 0,w = scc_id[i]; i < scc_id.size(); ++i,w = scc_id[i]) {
            if (w == m_id) {
                c.push_back(i);
            }
        }
        return c;
    }
};


void test_dig_hasPath() {
    ifstream fin("tinyDG.txt");
    Digraph dG(fin);
    dG.print();
    DirectedDFS dir_dfs(dG,1);
    dir_dfs.print();
    DirectedDFS dir_dfs1(dG,{1, 2, 6});
    dir_dfs1.print();
}

// 检查是否有环
void test_dig_cycle() {
    ifstream fin("tinyDG.txt");
    Digraph dG(fin);
    dG.print();
    DirectedCycle dir_cycle(dG);
    if (dir_cycle.hasCycle()) {
        stack<int> st = dir_cycle.cycle();
        cout << "hasCycle: ";
        while (!st.empty()) {
            cout << st.top() << " ";
            st.pop();
        }
    } else {
        cout << "  tinyDG.txt has not cycle  "<< endl;
    }
}

// DepthFirstOrder 拓扑顺序
void test_dig_dfs_order() {
    ifstream fin("tinyDAG.txt");
    Digraph dG(fin);
    dG.print();
    
    DirectedCycle dir_cycle(dG);
    if (dir_cycle.hasCycle()) {
        stack<int> st = dir_cycle.cycle();
        cout << "hasCycle: ";
        while (!st.empty()) {
            cout << st.top() << " ";
            st.pop();
        }
        return;
    } else {
        cout << "tinyDAG.txt has not cycle  "<< endl;
    }
    
    DepthFirstOrder order(dG);
    stack<int> st = order.reversePost();
    if (!st.empty()) {
        cout << "reversePost-reverse: ";
        while (!st.empty()) {
            cout << st.top() << " ";
            st.pop();
        }
        cout << endl;
    } else {
        cout << "  tinyDG.txt has cycle  "<< endl;
    }
}


// 计算强连通分量

void test_dig_stronglyConnected() {
    ifstream fin("tinyDG.txt");
    Digraph dG(fin);
    dG.print();
    SCC scc(dG);
    scc.print();
}


int main(int argc, const char * argv[]) {
    // test_giraph();
//    test_dig_hasPath();
//    test_dig_cycle();
//    test_dig_dfs_order();
    test_dig_stronglyConnected();
    return 0;
}
