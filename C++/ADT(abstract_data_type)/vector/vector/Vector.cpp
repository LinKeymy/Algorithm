//
//  Vector.cpp
//  vector
//
//  Created by SteveLin on 2019/7/15.
//  Copyright © 2019 unixlin. All rights reserved.
//

#include <stdio.h>
#include <algorithm>
#include <iostream>

#define SPARE_CAPACITY 10

template <typename Element>
class Vecter {
private:
    int m_size;
    int m_capacity;
    Element *m_elements;
    
public:
    // constructor, explicit 必须显示调用，不能发生隐式转换。
    explicit Vecter(int init_size = 0) : m_size(init_size),m_capacity(SPARE_CAPACITY + init_size){
        m_elements = new Element[m_capacity];
    }
    
    // copy constructor
    Vecter(const Vecter& rhs): m_size(rhs.m_size),m_capacity(rhs.m_capacity),m_elements(nullptr) {
        m_elements = new Element[m_capacity];
        for (int i = 0; i < m_size; ++i) {
            m_elements[i] = rhs.m_elements[i];
        }
    }
    
    // copy assignment
    Vecter& operator= (const Vecter& rhs) {
        // 调用拷贝构造 Vecter copy 创建了一个未初始化的实例
        Vecter copy = rhs;
        std::swap(copy, *this); // this 指向 刚copy好的对象
        return *this;
    }
    
    // destructor
    ~Vecter() {
        if (m_elements) {
            delete [] m_elements;
            std::cout << "delete m_elements" << std::endl;
        }
    }
    
    // move constructor // 转移构造 右值 初始化 直接使用rhs的资源，然后然后抹掉rhs资源的拥有权。
    Vecter(Vecter && rhs): m_size(rhs.m_size), m_capacity(rhs.m_capacity),m_elements(rhs.m_elements) {
        rhs.m_elements = nullptr;
        rhs.m_size = 0;
        rhs.m_capacity = 0;
    }
    
    // move assignment  转移赋值
    Vecter & operator= ( Vecter&& rhs) {
        std::swap(m_size, rhs.m_size);
        std::swap(m_capacity, rhs.m_capacity);
        std::swap(m_elements, rhs.m_elements);
        return *this;
    }
    
    
    // 更新容器m_size
    void rem_size(int newm_size) {
        if (newm_size > m_capacity) {
            reserve (newm_size * 2);
        }
        m_size = newm_size;
    }
    
    // 更新容器m_capacity
    void reserve(int newm_capacity) {
        if (newm_capacity < m_size) {
            return;
        }
        
        Element *newArray = new Element[newm_capacity];
        for (int i = 0; i < m_size; ++i) {
            newArray[i] = m_elements[i];
        }
        m_capacity = newm_capacity;
        std::swap(newArray, m_elements);
        delete [] newArray;
    }
    
    // 容器的下标search
    Element & operator[] (int index) {
        if (index > m_size -1) {
            return nullptr;
        }
        return m_elements[index];
    }
    
    const Element & operator[] (int index) const {
        if (index > m_size -1) {
            return nullptr;
        }
        return m_elements[index];
    }
    
    // empty
    bool empty() const {
        return size() == 0;
    }
    
    int size() {
        return m_size;
    }
    
    int capacity() {
        return m_capacity;
    }
    
    
    // push
    
    void push_back(const Element & e) {
        
        if (m_size == m_capacity) {
            reserve(2 * m_capacity + 1);
        }
        // 这是对e的一次拷贝
        m_elements[m_size++] = e;
    }
    
    void push_back(Element && e) {
        if (m_size == m_capacity) {
            // +1 为了处理大小为0的情况
            reserve(2 * m_capacity + 1);
        }
        // 是直接move 因为 e 是右值，销毁浪费
        m_elements[m_size++] = std::move(e);
    }
    
    // pop
    void pop_back() {
        --m_size;
    }
    
    // back
    const Element & back() const {
        return m_elements[m_size - 1];
    }
    
    typedef  Element * iterator;
    typedef const Element * const_iterator;
    
    
    // begin
    iterator begin() {
        return &m_elements[0];
    }
    
    const_iterator begin() const {
        return &m_elements[0];
    }
    
    // end 这里不是指向最后一个元素的开始，而是最后一个元素的的结尾
    
    iterator end() {
        return &m_elements[m_size];
    }
    
    const_iterator end() const {
        return &m_elements[m_size];
    }
};
