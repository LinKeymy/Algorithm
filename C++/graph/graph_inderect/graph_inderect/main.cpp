//
//  main.cpp
//  graph_inderect
//
//  Created by SteveLin on 2019/8/14.
//  Copyright © 2019 SteveLin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "union-find.cpp"

using namespace std;

vector<string> readWords( istream & in ) {
    string oneLine;
    vector<string> v;
    
    while( in >> oneLine )
        v.push_back( oneLine );
    
    return v;
}


class Graph {
private:
    int m_v;
    int m_e;
    int m_re;
    vector<list<int> *> adj;
public:
    Graph(int n) {
        init(n);
    }
    
    void init(int n) {
        m_v = n;
        m_e = 0;
        adj = vector<list<int> *>(n);
        for (int v = 0; v < n; ++v) {
            adj[v] = new list<int>();
        }
    }
    Graph(istream & in) {
        string oneLine;
        in >> oneLine;
        init(stoi(oneLine));
        in >> oneLine;
        m_re = stoi(oneLine);
        string v;
        string w;
        while( in >> v && in >> w) {
            int iv = stoi(v);
            int iw = stoi(w);
            addEdge(iv, iw);
        }
    }
    int V() const {
        return m_v;
    }
    int E() const {
        return m_re;
    }
    
    void addEdge(int v, int w) {
        adj[v]->push_front(w);
        adj[w]->push_front(v);
        ++m_e;
    }
    
    list<int> & adjacent(int v) const {
        return *adj[v];
    }
    
    static int degree(const Graph & G, int v) {
        return (int)G.adjacent(v).size();
    }
    
    static int maxDegree(const Graph & G) {
        int max = 0;
        for (int v = 0; v < G.V(); ++v) {
            if (G.adjacent(v).size() > max) max = (int)G.adjacent(v).size();
        }
        return max;
    }
    
    static double avgDegree(const Graph & G) {
        return 2.0 * G.E() / G.V();
    }
    
    // 自环：连接到自身的点
    static int numberOfSelfLoops(const Graph & G) {
        int count = 0;
        for (int v = 0; v < G.V(); ++v) {
            for (int w : G.adjacent(v)) {
                if (v == w) count++;
            }
        }
        return count / 2;
    }

    static void printGraph(const Graph & G) {
        cout << G.V() << "  vertices, " << G.E() << "  deges" << endl;
        for (int v = 0; v < G.V(); ++v) {
            cout << v << ": " ;
            for (int w : G.adjacent(v)) {
                cout << w << " ";
            }
            cout << endl;
        }
    }
};


int main(int argc, const char * argv[]) {
    Graph g(10);
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
    return 0;
}
