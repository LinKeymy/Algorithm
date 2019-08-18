//
//  main.cpp
//  graph_inderect
//
//  Created by SteveLin on 2019/8/14.
//  Copyright © 2019 SteveLin. All rights reserved.
//

#include "union-find.cpp"
#include "DepthFirstPaths.cpp"
#include <stack>
#include <queue>

# pragma - mark 使用广度优先搜索求解最小路径
// bsf 是层序遍历的推广 (bsf 生成棵搜索树)
class BreadthFirstSearch {
private:
    vector<bool> *v_marked;
    vector<int> *edgeTo;
    int s;
    
public:
    BreadthFirstSearch(const Graph & G, int s) {
        v_marked = new vector<bool>(G.V(),false);
        edgeTo = new vector<int>(G.V());
        this->s = s;
        bsf(G, s);
    }
    
    ~BreadthFirstSearch() {
        if (v_marked) {
            delete v_marked;
        }
        if (edgeTo) {
            delete edgeTo;
        }
    }
    
    bool marked(int v) {
        return (*v_marked)[v];
    }
    
    // 广度优先bsf，是谁先到达，谁标记，已标记的点不处理
    // 使用队列，这是层序遍历的推广，不使用递归。
    void bsf(const Graph & G, int s) {
        queue<int> q;
        (*v_marked)[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : G.adjacent(v)) {
                if (!marked(w)) {
                    (*v_marked)[w] = true;
                    (*edgeTo)[w] = v;
                    q.push(w);
                }
            }
        }
    }
    
    bool hasPathTo(int v) const {
        return (*v_marked)[v];
    }
    
    stack<int> pathTo(int v) const {
        stack<int> st;;
        for (; v != s; v = (*edgeTo)[v]) {
            st.push(v);
        }
        st.push(s);
        return st;
    }
};

# pragma - mark 连通性
class CC {
private:
    // 这里也可以节省一个 v_marked 数组，将v_marked声明为 vector<int> *v_marked
    // 对于marked的顶点 v 设置为 m_count 前 m_count 大于 0，检查 v_marked索引的值大于0 表述marked
    vector<bool> *v_marked;
    vector<int> *id;
    int m_count;
    
public:
    CC(const Graph & G) {
        v_marked = new vector<bool>(G.V(),false);
        id = new vector<int>(G.V(),0);
        m_count = 0;
        for (int v = 0; v < G.V(); ++v) {
            if (!markd(v)) {
                dfs(G, v);
                ++m_count;
            }
        }
    }
    
    ~CC() {
        if (id) {
            delete id;
            id = nullptr;
        }
        if (v_marked) {
            delete  v_marked;
            v_marked = nullptr;
        }
    }
    
    bool markd(int v) {
        return (*v_marked)[v];
    }
    
    void dfs(const Graph & G, int v) {
        stack<int> st;
        st.push(v);
        while (!st.empty()) {
            v = st.top();
            st.pop();
            (*v_marked)[v] = true; // 出栈 mark
            (*id)[v] = m_count; // mark 后 打上 id
            for (int w : G.adjacent(v)) {
                if (!markd(w)) {
                    st.push(w);
                }
            }
        }
    }
    
    bool connected(int v, int w) {
        return (*id)[v] == (*id)[w];
    }
    
    int count() {
        return m_count;
    }
    
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
        for (int i = 0,w = (*id)[i]; i < (*id).size(); ++i,w = (*id)[i]) {
            if (w == m_id) {
                 c.push_back(i);
            }
        }
        return c;
    }
    
};

# pragma - mark 判断是否有环
class Cycle {
private:
    vector<bool> v_marked;
    bool m_hasCycle;
public:
    Cycle(const Graph & G) {
        v_marked = vector<bool> (G.V(),false);
        m_hasCycle = false;
        for (int v = 0; (!m_hasCycle) && (v < G.V()); ++v) { // 确定有环后就停止
            if (!marked(v)) {
                dfs(G, v, v);
            }
        }
    }
    
    bool marked(int v) {
        return v_marked[v];
    }
    
    bool hasCycle() {
        return m_hasCycle;
    }
    
    void dfs(const Graph & G, int s, int v) {  // 在dfs搜索树上，s 节点是 v 节点的 父 节点
        v_marked[v] = true;
        for (int w : G.adjacent(v)) {
            if (!marked(w)) {
                dfs(G, v, w);
            } else {
                if (s != w) {
                    // 在dfs搜索树上，和v链接的已经被标记，而且被标记的不是v的父亲节点
                    // 一定有环，而且环经过当前的v和w
                    m_hasCycle = true;
                }
            }
        }
    }
    
};


# pragma - mark 二分图
class TwoColor {
private:
    vector<bool> v_marked;
    vector<bool> v_color;
    bool m_isTwoColor = true;
    
public:
    TwoColor(const Graph & G) {
        v_marked = vector<bool> (G.V(), false);
        v_color = vector<bool>(G.V());
        for (int v = 0; v < G.V(); ++v ) {
            if (!marked(v)) {
                dfs(G, v);
            }
        }
    }
    
    bool marked(int v) {
        return v_marked[v];
    }
    
    void dfs(const Graph & G, int v) {
        v_marked[v] = true;
        bool vColor = v_color[v];
        for (int w : G.adjacent(v)) {
            if (!marked(w)) {
                v_color[w] = !vColor;
                dfs(G, w);
            } else {
                if (vColor == v_color[w]) { m_isTwoColor = false; }
            }
        }
    }
    
    bool isTwoColor() {
        return m_isTwoColor;
    }
    
};

// union_find 可以检查图是否为连通图，和任意两个点之间是否连通。
void test_Graph_union_find() {
    ifstream fin( "tinyG.txt" );
    Graph finG(fin);
    Graph::printGraph(finG);
    
    UF uf(finG.V());
    for (int i = 0; i < finG.V(); ++i) {
        list<int> list = finG.adjacent(i);
        auto begin = list.begin();
        while (begin != list.end()) {
            uf.quick_union(i, *begin);
            ++begin;
        }
    }
    cout << uf.count() << endl;
}


void test_Graph_Search_dsf_Paths() {
    ifstream fin("tinyCG.txt");
    Graph finG(fin);
    DepthFirstPaths paths(finG,0);
    stack<int> *st = paths.pathTo(5);
    DepthFirstPaths::printPath(*st);
    stack<int> *st1 = paths.pathTo(4);
    DepthFirstPaths::printPath(*st1);
    delete st;
    delete st1;
}

void test_Graph_Search_bsf_Paths() {
    ifstream fin("tinyCG.txt");
    Graph finG(fin);
    BreadthFirstSearch paths(finG,0);
    stack<int> st = paths.pathTo(4);
    DepthFirstPaths::printPath(st);
}

void test_cc() {
    ifstream fin("tinyG.txt");
    Graph finG(fin);
    Graph::printGraph(finG);
    CC cc(finG);
    cc.print();

}

void test_cycle() {
    ifstream fin("unCycleG.txt");
    Graph finG(fin);
    Graph::printGraph(finG);
    Cycle cycle(finG);
    cout << "hasCycle: " << cycle.hasCycle() << endl;
}

void test_twoColor() {
    ifstream fin("twoColor.txt");
    Graph finG(fin);
    Graph::printGraph(finG);
    TwoColor twoColor(finG);
    cout << "twoColor: " << twoColor.isTwoColor() << endl;
}



int main(int argc, const char * argv[]) {
    
    test_cc();

    return 0;
}


