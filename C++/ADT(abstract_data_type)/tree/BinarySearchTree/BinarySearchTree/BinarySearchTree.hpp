//
//  BinarySearchTree.hpp
//  BinarySearchTree
//
//  Created by SteveLin on 2019/7/20.
//  Copyright © 2019 unixlin. All rights reserved.
//

#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>

#endif /* BinarySearchTree_hpp */


template <typename Comparable>
struct BinaryNode {
    Comparable m_element;
    BinaryNode *left;
    BinaryNode *right;
    
    BinaryNode(const Comparable & element,BinaryNode *lt = nullptr, BinaryNode *rt = nullptr)
    : m_element(element),left(lt),right(rt) {};
    BinaryNode(Comparable && element,BinaryNode *lt = nullptr, BinaryNode *rt = nullptr)
    : m_element(std::move(element)),left(lt),right(rt) {};
    ~BinaryNode() {
        std::cout << " ~BinaryNode(): " << m_element << std::endl;
    }
};


template <typename Comparable>
class BinarySearchTree {
    
public:
//     构造函数 no return
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree & rhs);
    BinarySearchTree(BinarySearchTree && rhs);
    ~BinarySearchTree();

    // assign 函数 return for =
    BinarySearchTree & operator= (const BinarySearchTree & rhs); // copy assign
    BinarySearchTree & operator= (BinarySearchTree && rhs);  // move assign

    // 查
    const Comparable & findMax() const;
    const Comparable & findMin() const;
    bool contains(const Comparable & x) const;
    bool empty() const;
    void printTree(std::ostream & out = std::cout) const;

    // 增 、 删
    void clear();
    void insert(const Comparable & x);
    void insert(Comparable && x);
    void remove(const Comparable & x);
    
    // order
    void preorder() { preorder_traversal(root); };
    void inorder() { inorder_traversal(root); };
    void postorder() { postorder_traversal(root); };
    void levelorder() { levelorder_traversal(root); };
    
    
    void inorder_traversal_using_stack() { inorder_traversal_using_stack(root); };
    
    // reverse
    void reverse() { reverse(root); };


    BinaryNode<Comparable> *root;

    /*
     *& 指针引用 引用一个 指针变量
     (函数外部的一个指针变量被引用，那么函数传入的参数等效于直接使用外部变量操作)
     */
    void insert(const Comparable & x, BinaryNode<Comparable> * & t );
    void insert(Comparable && x, BinaryNode<Comparable> * & t );
    void remove(const Comparable & x, BinaryNode<Comparable> * & t);

    BinaryNode<Comparable> * findMin(BinaryNode<Comparable> * t) const;
    BinaryNode<Comparable> * findMax(BinaryNode<Comparable> * t) const;

    bool contains(const Comparable & x, BinaryNode<Comparable> * t) const;
    BinaryNode<Comparable> * & constainsAtNode(const Comparable & x, BinaryNode<Comparable> * & t) const;
    void printTree(BinaryNode<Comparable> * t, std::ostream & cout) const;
    BinaryNode<Comparable> * clone(BinaryNode<Comparable> * t) const;

    void clear(BinaryNode<Comparable> * & t);
    friend std::ostream & operator<<(std::ostream &, BinaryNode<Comparable> * t) ;
    
    
    // 遍历
    /* - - - - - - - - -  recuision solution - - - - - - - - - - -*/
    void preorder_traversal(BinaryNode<Comparable> * t) {
        if (t == nullptr) return;
         // 前序遍历，访问放在递归左右子树的前边
        std::cout << t->m_element << std::endl;
        if (t->left != nullptr) {
            preorder_traversal(t->left);
        }
        if (t->right != nullptr) {
            preorder_traversal(t->right);
        }
    }
    
    void postorder_traversal(BinaryNode<Comparable> * t) {
        if (t == nullptr) return;
        if (t->left != nullptr) {
            postorder_traversal(t->left);
        }
        if (t->right != nullptr) {
            postorder_traversal(t->right);
        }
        // 后序遍历，访问放在递归左右子树的后边
        std::cout << t->m_element << std::endl;
    }
    
    void inorder_traversal(BinaryNode<Comparable> * t) {
        if (t == nullptr) return;
        if (t->left != nullptr) {
            inorder_traversal(t->left);
        }
         // 中序遍历，访问放在递归左右子树的中间
        std::cout << t->m_element << std::endl;
        if (t->right != nullptr) {
            inorder_traversal(t->right);
        }
        
    }
    
     /* - - - - - - - - -  queue solution - - - - - - - - - - -*/
    // 这里的层序遍历使用的是队列，让root第一个进入，然后出来入一个node，访问node元素后，将其走右节点入队。
    void levelorder_traversal(BinaryNode<Comparable> * t) {
        std::ostream &out = std::cout;
        out << "[ ";
        std::queue<BinaryNode<Comparable> *> q;
        if (t != nullptr) {
            q.push(t);
        }
        while (!q.empty()) {
            BinaryNode<Comparable> *front = q.front();
            out << front->m_element << " ";
            q.pop();
            if (front->left != nullptr) {
                q.push(front->left);
            }
            if (front->right != nullptr) {
                q.push(front->right);
            }
        };
        out << "]" << std::endl;
    }
    
     /* - - - - - - - - -  stack solution - - - - - - - - - - -*/
    void inorder_traversal_using_stack(BinaryNode<Comparable> * t) {
        if (t == nullptr) return;
        std::stack<BinaryNode<Comparable> *> st_node;
        while (1) {
            if (t != nullptr) {
                st_node.push(t);  // 该节点的左子树情况不清晰，先将它设置为待访问
                t = t->left;
            }

            if (t == nullptr) {  // 如果没左子树
                if (st_node.empty()) return;
                // 可以访问节点
                BinaryNode<Comparable> *top = st_node.top();
                st_node.pop();
                std::cout << top->m_element << std::endl;
                // 查看右访问右子树
                t = top->right; // 如果有右子树重复前面的操作访问右子树
            }
        }
    }
    
    void reverse(BinaryNode<Comparable> * t) {
        if (t != nullptr) {
            BinaryNode<Comparable> *tmp = t->left;
            t->left = t->right;
            t->right = tmp;
            reverse(t->left);
            reverse(t->right);
        }
    }
};


template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree() {};

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree & rhs) {
    root = clone(rhs.root);
}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree && rhs) {
    
}

template <typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree() {
    clear();
}


template <typename Comparable>
BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator= (const BinarySearchTree & rhs) {
    BinarySearchTree<Comparable> tmpBst = rhs;
    this->root = tmpBst.root;
    tmpBst.root = nullptr;  // 这是很多其他语言使用者刚接触到C++非常容易遗漏的点。
    return *this;
}

template <typename Comparable>
BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator= (BinarySearchTree && rhs) {
    return rhs;
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::empty() const {
    return root == nullptr;
}


template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable &x) const {
    return contains(x, root);
}

template <typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin() const {
    return findMin(root)->m_element;  // ? 这里是否需要处理防止 findMin(root) 为 null
}

template <typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax() const {
    return findMax(root)->m_element; // ? 这里是否需要处理防止 findMin(root) 为 null
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printTree(std::ostream & out) const {
    BinarySearchTree::printTree(root, out);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::clear() {
    clear(root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x) {
    insert(x, root);
}
template <typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable && x) {
    insert(std::move(x), root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable & x) {
    remove(x, root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x, BinaryNode<Comparable> * & t ) {
    if (t == nullptr) {
        root = new BinaryNode<Comparable>(x);
        return;
    }
    if (x < t->m_element) {
        insert(x, t->left);
    } else if (t->m_element < x) {
        insert(x, t->right);
    }
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable && x, BinaryNode<Comparable> * & t ) {
    if (t == nullptr) {
        t = new BinaryNode<Comparable>(std::move(x));
        return;
    }
    if (x < t->m_element) {
        insert(std::move(x), t->left);
    } else if (t->m_element < x) {
        insert(std::move(x), t->right);
    }
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable & x, BinaryNode<Comparable> * & t) {
    if (t != nullptr) {
        BinaryNode<Comparable> * & node = constainsAtNode(x,t);
        if (node == nullptr) return;
        if (node->left == nullptr && node->right == nullptr) {  // 0 个子节点
            delete node; node = nullptr;
            
        } else if (node->left != nullptr && node->right != nullptr) { // 2 个子节点
            BinaryNode<Comparable> *successor = node->right;
            BinaryNode<Comparable> *successor_parent = node;
            while (successor->left != nullptr) {
                successor_parent = successor;
                // 能进入 while  successor->left ！= nullptr 故跳出while时 successor ！=  nullptr
                successor = successor->left;
            }
            // 使用后驱节点替换掉remove节点的值
            std::cout << "successor: " <<  successor->m_element <<  ",  replace:  " << node->m_element << std::endl;
            node->m_element = successor->m_element;
            if (node->right->left) { // 出现左拐
                if (successor->right != nullptr) { // successor 非叶子节点
                    successor_parent->left = successor->right;
                } else {  // successor 是叶子节点
                    delete successor;
                    successor_parent->left = nullptr;
                }
            } else {  // 没有左拐，那么 successor 就是 node 的右节点
                node->right = successor->right;
                delete successor;
            }
        } else { // 1 个子节点
            if (node->left != nullptr) {
                BinaryNode<Comparable> *tmp = node;
                node = node->left;
                delete tmp;
            }
            
            if (node->right != nullptr) {
                BinaryNode<Comparable> *tmp = node;
                node = node->right;
                delete tmp;
            }
        }

    }
}
template <typename Comparable>
BinaryNode<Comparable> * & BinarySearchTree<Comparable>::constainsAtNode(const Comparable & x, BinaryNode<Comparable> * & t) const {
    if (t == nullptr) {
        return t;
    }
    if (x < t->m_element) {
        return constainsAtNode(x, t->left);
    } else if (t->m_element < x) {
        return constainsAtNode(x, t->right);
    } else {
        return t;
    }
}

template <typename Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMin(BinaryNode<Comparable> * t) const {
    if (t != nullptr) {
        while (t->left != nullptr) {
             t = t->left;
        }
    }
    return t;
}

template <typename Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMax(BinaryNode<Comparable> * t) const {
    while (t->right != nullptr) {
        t = t->right;
    }
    return t;
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable & x, BinaryNode<Comparable> * t) const {
    return constainsAtNode(x, t) != nullptr;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode<Comparable> * t, std::ostream & cout) const {
    cout << "[ ";
    std::stack<BinaryNode<Comparable> *> st;
    if (t != nullptr) {
        st.push(t);
    } else {
        cout << "null_root]";
    }
    while (!st.empty()) {
        BinaryNode<Comparable> *top = st.top();
        cout << top->m_element << " ";  // 先序遍历打印
        st.pop();
        if (top->right != nullptr) {
            st.push(top->right);
        }
        if (top->left != nullptr) {
            st.push(top->left);
        }
    }
    cout << "]" << std::endl;
}


template <typename Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::clone(BinaryNode<Comparable> * t) const {
    if (t == nullptr) return nullptr;
     // BinaryNode<Comparable> * node = BinaryNode<Comparable>(t->m_element,clone(t->left),t->right);
    BinaryNode<Comparable> * node = new BinaryNode<Comparable>(t->m_element,t->left,t->right);
    node->left = clone(t->left);
    node->right = clone(t->right);
    return node;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::clear(BinaryNode<Comparable> * & t) {
    /*
     // 这样的递归会更加清晰，但是在 t->left,t->right 等为 null的时候会有不必要的函数调用开销
     if (t != nullptr) {
     clear(t->left);
     clear(t->right);
     delete t;
     }
     t = nullptr;
     */
    
    if (t != nullptr) {
        clear(t->left);
        clear(t->right);
        delete t;
    }
    t = nullptr;
//    if (t == nullptr) return;
//    if (t->left != nullptr) {
//        clear(t->left);
//    }
//
//    if (t->right != nullptr) {
//        clear(t->right);
//    }
//    delete t;
//    t = nullptr;
}


//
//template <typename Comparable>
//std::ostream & operator<<(std::ostream & cout, const BinaryNode<Comparable> * t) {
//    cout << "[";
//
//    std::stack<BinaryNode<Comparable>> st;
//    if (t != nullptr) {
//        st.push(t);
//    } else {
//        cout << "null_root]";
//        return cout;
//    }
//    if (!st.empty()) {
//        BinaryNode<Comparable> top = st.top();
//        cout << top->m_element;
//        st.pop();
//        if (top->right != nullptr) {
//            st.push(top->right);
//        }
//        if (top->left != nullptr) {
//            st.push(top->left);
//        }
//    }
//    cout << "]";
//    return cout;
//}

