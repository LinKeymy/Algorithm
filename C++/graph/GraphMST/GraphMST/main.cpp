//
//  main.cpp
//  GraphMST
//
//  Created by SteveLin on 2019/8/17.
//  Copyright © 2019 SteveLin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
using namespace std;




class IndexMinPQ {
private:
    vector<double> v;
    priority_queue<double,vector<double>,greater<double>> pq;
public:
    IndexMinPQ() {
        v = vector<double>{};
        pq = priority_queue<double,vector<double>,greater<double>>{};
        
    }
    IndexMinPQ(int n) {
        v = vector<double>(n,RLIM_INFINITY);
        pq = priority_queue<double,vector<double>,greater<double>>{};
    }
    
    void insert(int k, double item) {
        if (k < v.size()) {
            if (v[k]  != RLIM_INFINITY) {
                throw "bad index";
            }
            v[k] = item;
            pq.push(item);
    
        }
    }
    
    void change(int k, double item) {
        if (k >= v.size()) throw "bad index";
        if (v[k] == RLIM_INFINITY) throw "bad index";
        v[k] = item;
        pq = priority_queue<double,vector<double>,greater<double>>{};
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] != RLIM_INFINITY) {
                pq.push(v[i]);
            }
        }
    }
    
    bool contains(int k) {
        return v[k] != RLIM_INFINITY;
    }
    
    bool isEmpty() {
        return pq.empty();
    }
    
    double min() {
        return pq.top();
    }
    
    int pop() {
        for (int i = 0; i < v.size(); ++i) {
            if (v[i] == min()) {
                v[i] = RLIM_INFINITY;
                pq.pop();
                return i ;
            }
        }
       throw "bad pop";
    }

};

class Edge {
private:
    int m_v;
    int m_w;
    double m_weight;
   
    
public:
     Edge(int v = - 1, int w = - 1, double weight = RLIM_INFINITY):m_v{v},m_w{w},m_weight{weight} {
         
     }
    
//    Edge(){
//
//    }
    
    double weight() const {
        return m_weight;
    }
    int either() const {
        return m_v;
    }
    int other(int vertex) const {
        if (vertex == m_v) return m_w;
        if (vertex == m_w) return m_v;
        else throw "bad news";
    }
    bool operator < (const Edge & e) const{
        return (this->weight() > e.weight());
    }
    
    
    bool operator > (const Edge & e) const {
        return (this->weight() > e.weight());
    }
    
    bool operator == (const Edge & e) const {
        return (this->weight() == e.weight());
    }
    void print() const {
        cout << " ( " << m_v << "——" << m_w << " , " << m_weight <<  " )";
    }
};

class EdgeWeightedGraph {
    
private:
    int m_v;
    int m_e;
    int m_re;
    vector<list<Edge*>> adj;
    
    void init(int n) {
        m_v = n;
        m_e = 0;
        adj = vector<list<Edge*>>(n);
        for (int v = 0; v < n; ++v) {
            (adj)[v] = list<Edge*>{};
        }
    }
    
    
public:
    
    EdgeWeightedGraph(int v) {
        adj = vector<list<Edge*>>(v);
    }
    EdgeWeightedGraph(ifstream & in) {
        string oneLine;
        in >> oneLine;
        init(stoi(oneLine));
        in >> oneLine;
        m_re = stoi(oneLine);
        string v;
        string w;
        string weight;
        while( in >> v && in >> w && in >> weight) {
            int iv = stoi(v);
            int iw = stoi(w);
            double ie = stod(weight);
            Edge *e = new Edge(iv,iw,ie);
            addEdge(e);
        }
    }
    
    ~EdgeWeightedGraph() {
        for (int v = 0; v < m_v; ++v ) {
            while (!adj[v].empty()) {
                Edge *e = adj[v].back();
                int w = e->other(v);
                adj[v].pop_back();
                auto begin = adj[w].begin();
                while (begin != adj[v].end()) {
                    if ((*begin)->other(w) == v) {
                        adj[w].erase(begin);
                        break;
                    }
                    ++begin;
                }
                if (e) delete e;
            }
        }
    }
    
    
    int v() const {
        return m_v;
    }
    int e() const {
        return m_e;
    }
    void addEdge(Edge *e) {
        int v = e->either(), w = e->other(v);
        // 一条无向边属于两个点
        adjacent(v).push_front(e);
        adjacent(w).push_front(e);
        ++m_e;
    }
    
    Edge* edgeForVW(int v, int w) const {
        list<Edge*> vlist = adjacent(v);
        for (Edge* e : vlist) {
            if (e->other(v) == w) return e;
        }
        return nullptr;
    }
    
    Edge* edgeForVW(const Edge &e) const {
        int v = e.either(), w = e.other(v);
        return edgeForVW(v, w);
    }
    
    list<Edge*>& adjacent(int v) {
        return adj[v];
    }
    list<Edge*> adjacent(int v) const {
        return adj[v];
    }
    // 所有的边
    list<Edge*> edges() {
        list<Edge*> es;
        for (int v = 0; v < this->v(); ++v)
            for (Edge *e :adjacent(v))
                if (e->other(v) > v)
                    es.push_front(e);
        return es;
    }
    
    void print() const{
        cout << m_v << "   vertex, "  << m_e <<  "  edges  " << endl;
        for (int v = 0; v < m_v; ++v) {
            cout << v << ": ";
            for (Edge *e : adjacent(v)) {
                int v = e->either(), w = e->other(v);
                double wei = e->weight();
                cout << " ( " << v << "——" << w << " , " << wei <<  " )";
            }
            cout << endl;
        }
    }
};


class MST {
public:
    MST(const EdgeWeightedGraph & G);
    list<Edge*> edges() {
        list<Edge*> ls;
        return ls;
    }
    
    double weight() {
        return 0;
    }
};



class LazyPrimMST {
private:
    vector<bool> v_marked;
    queue<Edge*> mst;
    priority_queue<Edge> pq;
public:
    
    
    
    LazyPrimMST(const EdgeWeightedGraph & G) {
        v_marked = vector<bool>(G.v(),false);
        mst = queue<Edge*>{};
        pq = priority_queue<Edge>{};
        //算法入口
        primMST(G);
    }
    
    bool marked(int v) {
        return v_marked[v];
    }
    
    void primMST(const EdgeWeightedGraph & G) {
        visit(G, 0);
        while (!pq.empty()) {
            Edge *minE = G.edgeForVW(pq.top());
            pq.pop();
            if (!minE) continue;
            int v = minE->either(), w = minE->other(v);
            if (marked(v) && marked(w)) continue;  // 在横切的已经两个点都mark过的边，出队列就好，它已经
            mst.push(minE); // N - 1 次调用
            if (!marked(v)) visit(G, v);
            if (!marked(w)) visit(G, w);
        }
    }
    
    // 访问顶点，marked顶点，边入优先队列
    void visit(const EdgeWeightedGraph & G, int v) {
        v_marked[v] = true;
        list<Edge*> vEdges = G.adjacent(v);
        for (Edge *e : vEdges) {
            pq.push(*e);
        }
    }
    
    double weight() {
        double wht = 0;
        queue<Edge*> tmp = edges();
        while (!tmp.empty()) {
            Edge *e = tmp.front();
            wht += (*e).weight();
            tmp.pop();
        }
        return wht;
    }
    
    queue<Edge*> edges() const {
        return mst;
    }
    
    void printMst() {
        cout << "mst:  " <<  endl;
        cout <<"weight: " <<  this->weight() <<  endl;;
        cout << "egdes: ";
        queue<Edge*> q = edges();
        while (!q.empty()) {
            Edge* e = q.front();
            q.pop();
            e->print();
        }
        cout << endl;
    }
};


class PrimMST {
private:
    vector<Edge> edgeTo;
    vector<double> distTo;
    vector<bool> v_marked;
    IndexMinPQ pq;
    
public:
    PrimMST(const EdgeWeightedGraph & G) {
        edgeTo = vector<Edge>(G.v(),Edge(-1, -1, 0));
        distTo = vector<double>(G.v(),RLIM_INFINITY);
        v_marked = vector<bool>(G.v(),false);
        pq = IndexMinPQ(G.v());
        prim(G);
    }
    
    void prim(const EdgeWeightedGraph & G) {
        pq.insert(0, 0.0);
        while (!pq.isEmpty()) {
            int in = pq.pop();
            visit(G, in);
        }
    }
    
    void visit(const EdgeWeightedGraph & G, int v) {
        v_marked[v] = true;
        for (Edge *e : G.adjacent(v)) {
            int w = e->other(v);
            if (marked(w)) continue; // 可能是上一个marked过的点
            if (e->weight() < distTo[w]) {
                if (pq.contains(w)) {
                    pq.change(w, e->weight());
                } else {
                    pq.insert(w, e->weight());
                }
                edgeTo[w] = *e; // 更新点w连接到最小生成树的最小权值边
                distTo[w] = e->weight(); // 更新点w连接到最小生成树的最小权值
            }
            
        }
    }
    
    bool marked(int v) {
        return v_marked[v];
    }
    
    double weight() const {
        double wht = 0;
        for (int i = 0; i < edgeTo.size(); ++i) {
            wht += edgeTo[i].weight();
        }
        return wht;
    }
    
    vector<Edge> edges() const {
        vector<Edge> ev(edgeTo.size() - 1);
        for (int i = 1; i < edgeTo.size(); ++i) {
            ev[i-1] = edgeTo[i];
        }
        return ev;
    }
    
    void printMst() const {
        cout << "mst:  " <<  endl;
        cout <<"weight: " <<  this->weight() <<  endl;;
        cout << "egdes: ";
        vector<Edge> q = edges();
        for (int i = 0; i < q.size(); ++i) {
            q[i].print();
        }
        cout << endl;
    }
};

void test_lazyMST() {
    ifstream fin("tinyEWG.txt");
    EdgeWeightedGraph wdg(fin);
    wdg.print();
    LazyPrimMST lazy(wdg);
    lazy.printMst();
}

void test_primMST() {
    ifstream fin("tinyEWG.txt");
    EdgeWeightedGraph wdg(fin);
    wdg.print();
    PrimMST prim(wdg);
    prim.printMst();
}

int main(int argc, const char * argv[]) {
    test_lazyMST();
    test_primMST();
    return 0;
}
