//
//  Digraph.hpp
//  Digraph
//
//  Created by SteveLin on 2019/8/16.
//  Copyright © 2019 SteveLin. All rights reserved.
//

#ifndef Digraph_hpp
#define Digraph_hpp

#include <stdio.h>
#include <fstream>
#include <list>
#include <vector>
#include <iostream>

#endif /* Digraph_hpp */

using namespace std;

class Digraph {
private:
    int m_e = 0;
    int m_v = 0;
    int m_re = 0;
    vector<list<int>> adj;
    
    void init(int n) {
        m_v = n;
        m_e = 0;
        adj = vector<list<int>>(n);
        for (int v = 0; v < n; ++v) {
            (adj)[v] = list<int>{};
        }
    }
    void addEdge(int v, int w) {
        adj[v].push_front(w);
        ++m_e;
    }
public:
    Digraph(int V) {
        init(V);
    }
    Digraph(istream & in) {
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
    
    int v() const {
        return m_v;
    }
    
    int e() const {
        return m_e;
    }
    
    list<int> adjacent(int v) const {
        return adj[v];
    }
    
    Digraph reverse() const {
        Digraph dir(this->v());
        for (int v = 0; v < this->v(); ++v) {
            for (int w : this->adj[v]) {
                dir.addEdge(w, v);
            }
        }
        return dir;
    }
    
    void print() {
        cout << this->v() << "  vertices, " << this->e() << "  deges" << endl;
        for (int v = 0; v < this->v(); ++v) {
            cout << v << ": " ;
            for (int w : this->adjacent(v)) {
                cout << w << " ";
            }
            cout << endl;
        }
        }
    
    
};
