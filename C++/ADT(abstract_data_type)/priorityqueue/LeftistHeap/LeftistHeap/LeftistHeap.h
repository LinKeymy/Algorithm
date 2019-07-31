//
//  LeftistHeap.h
//  LeftistHeap
//
//  Created by SteveLin on 2019/7/27.
//  Copyright © 2019 SteveLin. All rights reserved.
//

#ifndef LeftistHeap_h
#define LeftistHeap_h


#endif /* LeftistHeap_h */


template<typename Comparable>
class LeftistHeap {
public:
    LeftistHeap();
    LeftistHeap(const LeftistHeap & rhs);
    LeftistHeap(LeftistHeap && rhs);
    
    ~LeftistHeap();
    
    
    
    LeftistHeap & operator= (const LeftistHeap & rhs);
    LeftistHeap & operator= (LeftistHeap && rhs);
    
    bool emtpy() const;
    
    const Comparable & findMin() const;
    
    void insert(const Comparable & x);
    void insert(Comparable && x);
    void deleteMin();
    void deleteMin(Comparable & minItem);
    void clear();
    void merge(LeftistHeap & rhs);
    
    
private:
    
    struct LeftistNode {
        Comparable m_element;
        LeftistNode *left;
        LeftistNode *right;
        int null_path_lenght;
        
        LeftistNode(const Comparable & x, LeftistNode * lt = nullptr, LeftistNode * rt = nullptr, int npl = 0)
        : m_element{ x }, left{ lt }, right{ rt }, null_path_lenght { npl } { };
        
        LeftistNode(Comparable && x, LeftistNode * lt = nullptr, LeftistNode * rt = nullptr, int npl = 0)
        : m_element{ std::move(x) }, left{ lt }, right{ rt }, null_path_lenght { npl } { };
        
    };
    
    
    
};
