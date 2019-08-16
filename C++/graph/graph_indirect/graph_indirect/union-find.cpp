//
//  union-find.cpp
//  graph_inderect
//
//  Created by SteveLin on 2019/8/14.
//  Copyright © 2019 SteveLin. All rights reserved.
//


#include <iostream>
#include <vector>
using namespace std;

class UF {
private:
    vector<int> id;
    int m_count;
    
public:
    UF(int n) {
        m_count = n;
        id = vector<int>(n);
        for (int i = 0; i < n; ++i) {
            id[i] = i;
        }
    }
    
    int count() {
        return m_count;
    }
    
    bool quick_find_connected(int p, int q) {
        return quik_find(p) == quik_find(q);
    }
    
    bool quick_union_connected(int p, int q) {
        return quick_union_find(p) == quick_union_find(q);
    }
    
    // quik_find 对应的 quick_find_union 成本偏高
    int quik_find(int p) {
        return id[p];
    }
    
    void quick_find_union(int p, int q) {
        int pID = quik_find(p);
        int qID = quik_find(q);
        if (pID == qID) return;
        
        for (int i = 0; i < id.size(); ++i) {
            if (id[i] == pID) id[i] = qID;
        }
        --m_count;
    }
    
    // quick_union 对应的 quick_union_find 成本偏高
    void quick_union(int p, int q) {
        int pID = quick_union_find(p);
        int qID = quick_union_find(q);
        if (pID == qID) return;
        
        id[pID] = qID;
        --m_count;
    }
    
    int quick_union_find(int p) {
        while (p != id[p]) {
            p = id[p];
        }
        return p;
    }
};

// 加权的quick-union
class weightedQuickUnionUF {
private:
    vector<int> id;
    vector<int> sz;
    
    weightedQuickUnionUF(int n) {
        m_count = n;
        id = vector<int>(n);
        for (int i = 0; i < id.size(); ++i) {
            id[i] = i;
        }
        sz = vector<int>(n,1);
    }
    
    int m_count;
    
    int find(int p) {
        while (p != id[p]) {
            p = id[p];
        }
        return p;
    }
    
    /*
     将小的分量链接到大的分量中，若两个分量不相等，那么分量对于的树的高度不变
     树的高度降低，会大大降低 find 的成本，压缩路径对树高度增加的限制更显严格
     */
    void quick_union(int p, int q) {
        if (sz[p] < sz[q]) {
            id[p] = q;
            sz[q] += sz[p];
        } else {
            id[q] = p;
            sz[p] += sz[q];
        }
    }
};
