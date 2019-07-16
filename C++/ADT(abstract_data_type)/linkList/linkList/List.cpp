//
//  List.cpp
//  linkList
//
//  Created by SteveLin on 2019/7/16.
//  Copyright © 2019 unixlin. All rights reserved.
//

#include <iostream>


template <class Element>
class List {
private:
    // struct 通常用来直接被存取而不是通过方法访问数据的类
    struct Node {
        Element data;
        Node *prex;
        Node *next;
        
        // 左值初始化
        Node( const Element & e = Element(),Node *p = nullptr,Node *n = nullptr)
        :data(e), prex(p),next(n) {  }
        
        // 右值初始化
        Node( Element && e,Node *p = nullptr,Node *n = nullptr)
        :data(std::move(e)), prex(p),next(n) {  }
    };
    
public:
    
    class const_iterator {
        
    public:
        const_iterator():current(nullptr) { }
        
        const Element & operator* () {
            return retrieve();
        }
        
        // ++ 前缀
        const_iterator  & operator++ () {
            current = current->next;
            return *this;
        }
        
         // ++ 后缀
        const_iterator operator++(int) {
            // 原来的值用于返回
            const_iterator old = *this;
            ++(*this);
            return old;
        }
        
        // -- 前缀
        const_iterator  & operator-- () {
            current = current->prex;
            return *this;
        }
        
        // -- 后缀
        const_iterator operator--(int) {
            // 原来的值用于返回
            const_iterator old = *this;
            --(*this);
            return old;
        }
        
        
        // 判断一个 const_iterator 是否相等，是查看它们是否指向同一个Node
        bool operator== (const const_iterator & rhs) const {
           return current == rhs.current;
        }
        
        bool operator!= (const const_iterator & rhs) const {
            return !((*this) == rhs);
        }

    protected:
        // 当前节点
        Node *current;
        // 放回Node的中保存的数据
        Element & retrieve() const {
            return current->data;
        }
        // 使用一个节点指针的构造器
        const_iterator(Node *p): current(p) {}
        friend class List<Element>;
    };
    
    // const 可以用在 un_const ，可变处可以使用不可变，
    // 不可变处使用可变则违反了不可变的特性，这是禁止的
    class iterator: public const_iterator {
    public:
        iterator() {}
        // 可以通过对 Element 的引用进行修改iteraor中的Node的data的数据
        Element & operator* () {
            return const_iterator::retrieve();
        }
        
        const Element & operator* () const {
            // 直接调用const_iterator 的 operator*
            return const_iterator::operator*();
        }
        
        iterator & operator++ () {
            this->current = this->current->next;
            return *this;
        }
        
        iterator operator++ (int) {
            iterator old = *this;
            ++(*this);
            return old;
        }
        
        
        iterator & operator-- () {
            this->current = this->current->prex;
            return *this;
        }
        
        iterator operator-- (int) {
            iterator old = *this;
            --(*this);
            return old;
        }
        
    protected:
        iterator(Node *p): const_iterator(p){};
        friend class List<Element>;
    };
    
public:
    
    List() {
        init();
    }
    
    ~List() {
        clear();
        delete head;
        delete tail;
    }
    
    // copy constructor
    List(const List & rhs) {
        init();
        for (auto & e : rhs) {
            push_back(e);
        }
    }
    // copy assign
    List & operator= (const List & rhs) {
        // 调用copy constructor
        List copy = rhs;
        std::swap((*this), copy);
        return *this;
    }
    
    // move construct
    List(List && rhs): m_size(rhs.size()),head(rhs.head),tail(rhs.tail) {
        rhs.m_size = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    // move assign
    List & operator= (List && rhs) {
        std::swap(m_size, rhs.m_size);
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);
        return *this;
    }
    
    
    
    iterator begin() {
       return iterator(head->next);
    }
    
    const_iterator begin() const {
        return const_iterator(head->next);
    }
    
    iterator end() {
        return iterator(tail);
    }
    
    const_iterator end() const {
        return const_iterator(tail);
    }
    
    int size() const {
        return m_size;
    }
    
    bool empty() const {
        return size() == 0;
    }
    
    void clear() {
        while (!empty()) {
            pop_back();
        }
    }
    
    Element & front() {
        return *begin();
    }
    
    const Element & front() const {
        return *begin();
    }
    
    Element & back() {
        return *(--end());
    }
    
    const Element & back() const {
         return *(--end());
    }
    
    
    // push
    
    void push_front(const Element & e) {
        insert(begin(), e);
    }
    
    void push_front(Element && e) {
        insert(begin(), e);
    }
    
    void push_back(const Element & e) {
        insert(end(), e);
    }
    
    void push_back(Element && e) {
        insert(end(), e);
    }
    
    // pop
    void pop_front() {
        erase(begin());
    }
    
    void pop_back() {
        erase(--end());
    }
    
    iterator insert(iterator it, const Element & e) {
        Node *current = it.current;
        Node *node = new Node(e,current->prex,current);
        current->prex->next = node;  // 更新插入点前面一个node的next指向
        current->prex = node;  // 更新插入点后面一个node的prex指向
        m_size++;
        return iterator(node);
    }
    
    iterator insert(iterator it, Element && e) {
        Node *current = it.current;
        // 和上面一样，不同的是使用 e 是当作右值处理，这样赋值时直接move
        Node *node = new Node(std::move(e),current->prex,current);
        current->prex->next = node;
        current->prex = node;
        m_size++;
        return iterator(node);
    }
    
    iterator erase(iterator it) {
        Node *current = it.current;
        // 返回删链表除时的位置
        iterator retVal(current->next);
        current->prex->next = current->next;
        current->next->prex = current->prex;
        m_size--;
        delete current;
        return retVal;
    }
    
    iterator erase(iterator from, iterator to) { // to 位置不删除
        while (from != to) {
            from = erase(from);
        }
        return to;
    }
    
    
private:
    int m_size;
    Node *head;
    Node *tail;
    
    void init() {
        m_size = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prex = head;
    }
};
