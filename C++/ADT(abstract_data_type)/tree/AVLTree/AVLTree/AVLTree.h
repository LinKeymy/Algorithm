//
//  AVLTree.h
//  AVLTree
//
//  Created by SteveLin on 2019/7/23.
//  Copyright © 2019 unixlin. All rights reserved.
//

#ifndef AVLTree_h
#define AVLTree_h


#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>

#endif /* AVLTree_h */


using namespace std;

template <typename Comparable>
struct AvlNode {
    Comparable m_element;
    AvlNode *left;
    AvlNode *right;
    int height;
    
    AvlNode(const Comparable & element,AvlNode *lt = nullptr, AvlNode *rt = nullptr, int h = 0)
    : m_element(element),left(lt),right(rt),height(h) {};
    AvlNode(Comparable && element,AvlNode *lt = nullptr, AvlNode *rt = nullptr, int h = 0)
    : m_element(std::move(element)),left(lt),right(rt), height(h) {};
    ~AvlNode() {
        std::cout << " ~AvlNode(): " << m_element << std::endl;
    }
};


template <typename Comparable>
class AVLTree {
    
public:
    //     构造函数 no return
    AVLTree();
    AVLTree(const AVLTree & rhs);
    AVLTree(AVLTree && rhs);
    ~AVLTree();
    
    // assign 函数 return for =
    AVLTree & operator= (const AVLTree & rhs); // copy assign
    AVLTree & operator= (AVLTree && rhs);  // move assign
    
    // 查
    bool contains(const Comparable & x) const;
    bool empty() const;
    void printTree(std::ostream & out = std::cout) const;
    
    // 增 、 删
    void clear();
    void insert(const Comparable & x);
    void insert(Comparable && x);
    void remove(const Comparable & x);
    
    
    void inorder_traversal_using_stack() { inorder_traversal_using_stack(root); };
    
    // reverse
    void reverse() { reverse(root); };
    
    
    AvlNode<Comparable> *root;
    
    /*
     *& 指针引用 引用一个 指针变量
     (函数外部的一个指针变量被引用，那么函数传入的参数等效于直接使用外部变量操作)
     */
    void insert(const Comparable & x, AvlNode<Comparable> * & t );
    void insert(Comparable && x, AvlNode<Comparable> * & t );
    void remove(const Comparable & x, AvlNode<Comparable> * & t);
    
    bool contains(const Comparable & x, AvlNode<Comparable> * t) const;
    AvlNode<Comparable> * & constainsAtNode(const Comparable & x, AvlNode<Comparable> * & t) const;
    void printTree(AvlNode<Comparable> * t, std::ostream & cout) const;
    AvlNode<Comparable> * clone(AvlNode<Comparable> * t) const;
    
    void clear(AvlNode<Comparable> * & t);
    friend std::ostream & operator<<(std::ostream &, AvlNode<Comparable> * t) ;
    
    int height(AvlNode<Comparable> * t) {
        return t == nullptr ? -1 : t->height;
    }
    
    
    // balance
    
    
    int pathLenght(AvlNode<Comparable> * t) {
        if (t == nullptr) return -1;
        if (t->left == nullptr && t->right == nullptr) return 0;
        int leftPath = pathLenght(t->left);
        int rightPath = pathLenght(t->right);
        if (leftPath == -2 || rightPath == -2) return -2;
        if (abs(leftPath - rightPath) > 1) { return -2; };
        return max(leftPath, rightPath) + 1;
    }
    
    bool isBalance(AvlNode<Comparable> * t)  {
        if (t == nullptr || (t->left == nullptr && t->right == nullptr)) return true;
        stack<AvlNode<Comparable> *> st;
        vector<int> hn;
//        hn.reserve(10);
        st.push(t);
        AvlNode<Comparable> * last_t = t;
        while (!st.empty()) {
            AvlNode<Comparable> * top = st.top();
            if (top->left == nullptr && top->right == nullptr) { //
                st.pop();
                last_t = top;
                hn.push_back(0);
            } else if (top->left == last_t || top->right == last_t) {
                st.pop();
                last_t = top;
                if (top->left != nullptr && top->right != nullptr ) {
                    // last_t非叶子节点，那么需要知道top是否有两棵子树，如果是
                    // 左右子树已经被访问过，高度应该在栈顶
                    int last_1 = hn.back();
                    hn.pop_back();
                    int last_2 = hn.back();
                    hn.pop_back();
                    if (abs(last_1 - last_2) > 1) return false; // 不平衡出现
                    hn.push_back(max(last_1, last_2) + 1);
                } else {
                    int last_3 = hn.back() + 1;
                    if (last_3 > 1) return false;
                    hn.pop_back();
                    hn.push_back(last_3);
                }
            } else {
                if (top->left != nullptr) {
                    st.push(top->left);
                }
                if (top->right != nullptr) {
                    st.push(top->right);
                }
            }
        }
        return true;
    }
    
    static const int ALLOWED_IMBALANCE = 1;
    // 平衡过程是插入点开始，往上递归到树根
    void balance(AvlNode<Comparable> * & t) {
        if (t == nullptr)
            return;
        // 若失衡，先找出哪一棵子树比较深
        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) { // 左深
            // 左外
            // 等于的情况是出现于双旋过程的子过程 (这个说法是错误的)
            // 等于的情况是出现于删除导致失衡的情况，原本较深的左子树的左右两颗子树的高度可能相等。
            if (height(t->left->left) >= height(t->left->right)) {
                levelorderTraversal();
                rotateWithLeftChild(t);
                levelorderTraversal();  // 打印方便查看结果
            }
            // 左内
            else {
                levelorderTraversal();
                doubleRotateWithLeftChild(t);
                levelorderTraversal();
            }
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) { // 右深
            // 右外
            if (height(t->right->right) >= height(t->right->left)) {// 上面的判断条件保证这里是安全
                levelorderTraversal();
                rotateWithRightChild(t);
                levelorderTraversal();
            }
            //右内
            else {
                levelorderTraversal();
                doubleRotateWithRightChild(t);
                levelorderTraversal();
            }
        }
        // 若平衡，更新高度,这个是失衡点的高度，
        // 值得注意的是在适合点失衡点调节平衡时，左右子树的高度发生了改变
        // 如使得较深的那颗子树深度降低了1，也就是该子树的高度降低了1，也就是子树根的高度降低了1
        // 因此要在旋转的时候调整子树的高度，这里的高度才准确。
        t->height = max(height(t->left), height(t->right)) + 1;
    }
    
    // 将左子树的根，上移成为整棵子树的根
    void rotateWithLeftChild(AvlNode<Comparable> * & k2) {
        AvlNode<Comparable> * k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        // 更新高度
        k2->height = max(height(k2->left),height(k2->right)) + 1;
        k1->height = max(height(k1->left),height(k1->right)) + 1;
        
        std::cout << "rotateWithLeftChild: k2 = "<< k2->m_element << " , k1 = " << k1->m_element << std::endl;
        k2 = k1; // 左上移
       
    }
    
    // 将右子树的根，上移成为整棵子树的根
    void rotateWithRightChild(AvlNode<Comparable> * & k2) {
        AvlNode<Comparable> * k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        
        k2->height = max(height(k2->left),height(k2->right)) + 1;
        k1->height = max(height(k1->left),height(k1->right)) + 1;
        std::cout << "rotateWithLeftChild: k2 = "<< k2->m_element << " , k1 = " << k1->m_element << std::endl;
        k2 = k1; // 右上移
    }
    
    // 双旋-左子树 将左子树的右节点，上移成为整棵子树的根
    void doubleRotateWithLeftChild(AvlNode<Comparable> * & t) {
        std::cout << " - - - - -doubleRotateWithLeftChild start - - - - - - -" <<  std::endl;
        rotateWithRightChild(t->left);
        rotateWithLeftChild(t);
        std::cout << " - - - - -doubleRotateWithLeftChild finished - - - - - - -" <<  std::endl;
    }
    // 双旋-右子树 将右子树的左节点，上移成为整棵子树的根
    void doubleRotateWithRightChild(AvlNode<Comparable> * & t) {
        std::cout << " - - - - -doubleRotateWithRightChild start - - - - - - -" <<  std::endl;
        rotateWithLeftChild(t->right);
        rotateWithRightChild(t);
        std::cout << " - - - - -doubleRotateWithRightChild end - - - - - - -" <<  std::endl;
    }

    
    /* - - - - - - - - -  queue solution - - - - - - - - - - -*/
    // 这里的层序遍历使用的是队列，让root第一个进入，然后出来入一个node，访问node元素后，将其走右节点入队。
    vector<vector<int>> levelorderTraversal(AvlNode<Comparable> * t) {
        vector<vector<int>> v;
        vector<int> subV;
        subV.reserve(1);
        queue<AvlNode<int> *> st;
        if (t != nullptr) {
            st.push(t);
        }
        
        while (!st.empty()) {
            t = st.front();
            subV.push_back(t->m_element);
            st.pop();
            if (t->left != nullptr) { st.push(t->left); };
            if (t->right != nullptr) { st.push(t->right); };
            if (subV.size() == subV.capacity()) {
                v.push_back(subV);
                subV = vector<int>();
                subV.reserve(st.size());
            };
        }
        return v;
    }
    
    void levelorderTraversal() {
        vector<vector<int>> v = levelorderTraversal(root);
        auto it = v.begin();
        auto end = v.end();
        cout << "[";
        while (it != end) {
            cout << " [ ";
            auto vit = (*it).begin();
            auto vend = (*it).end();
            while (vit != vend) {
                cout << *vit << " ";
                ++vit;
            }
            if (vit != vend) {
                cout << "], ";
            } else {
                 cout << "]";
            }
           
            ++it;
        }
        cout << " ]" << endl;
    }
    
};
template <typename Comparable>
AVLTree<Comparable>::AVLTree() {};

template <typename Comparable>
AVLTree<Comparable>::AVLTree(const AVLTree & rhs) {
    root = clone(rhs.root);
}

template <typename Comparable>
AVLTree<Comparable>::~AVLTree() {
    clear();
}


template <typename Comparable>
AVLTree<Comparable> & AVLTree<Comparable>::operator= (const AVLTree & rhs) {
    AVLTree<Comparable> tmpBst = rhs;
    this->root = tmpBst.root;
    tmpBst.root = nullptr;  // 这是很多其他语言使用者刚接触到C++非常容易遗漏的点。
    return *this;
}

template <typename Comparable>
AVLTree<Comparable> & AVLTree<Comparable>::operator= (AVLTree && rhs) {
    return rhs;
}

template <typename Comparable>
bool AVLTree<Comparable>::empty() const {
    return root == nullptr;
}


template <typename Comparable>
bool AVLTree<Comparable>::contains(const Comparable &x) const {
    return contains(x, root);
}

template <typename Comparable>
void AVLTree<Comparable>::printTree(std::ostream & out) const {
    AVLTree::printTree(root, out);
}

template <typename Comparable>
void AVLTree<Comparable>::clear() {
    clear(root);
}

template <typename Comparable>
void AVLTree<Comparable>::insert(const Comparable & x) {
    insert(x, root);
}
template <typename Comparable>
void AVLTree<Comparable>::insert(Comparable && x) {
    insert(std::move(x), root);
}

template <typename Comparable>
void AVLTree<Comparable>::remove(const Comparable & x) {
    remove(x, root);
}

template <typename Comparable>
void AVLTree<Comparable>::insert(const Comparable & x, AvlNode<Comparable> * & t ) {
    if (t == nullptr) {
        root = new AvlNode<Comparable>(x);
        return;
    }
    if (x < t->m_element) {
        insert(x, t->left);
    } else if (t->m_element < x) {
        insert(x, t->right);
    }
    cout << "=====   ====   isBalance:       " << isBalance(root) << endl;;
    balance(t);
    cout << "=====   ====   isBalance:       " << isBalance(root) << endl;;
}

template <typename Comparable>
void AVLTree<Comparable>::insert(Comparable && x, AvlNode<Comparable> * & t ) {
    if (t == nullptr) {
        t = new AvlNode<Comparable>(std::move(x));
        return;
    }
    if (x < t->m_element) {
        insert(std::move(x), t->left);
    } else if (t->m_element < x) {
        insert(std::move(x), t->right);
    }
    cout << "=====   ====   isBalance:       " << isBalance(root) << endl;;
    balance(t);
    cout << "=====   ====   isBalance:       " << isBalance(root) << endl;;
}

template <typename Comparable>
void AVLTree<Comparable>::remove(const Comparable & x, AvlNode<Comparable> * & t) {
    if (t != nullptr) {
        AvlNode<Comparable> * & node = constainsAtNode(x,t);
        if (node == nullptr) return;
        if (node->left == nullptr && node->right == nullptr) {  // 0 个子节点
            delete node; node = nullptr;
            
        } else if (node->left != nullptr && node->right != nullptr) { // 2 个子节点
            AvlNode<Comparable> *successor = node->right;
            AvlNode<Comparable> *successor_parent = node;
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
                AvlNode<Comparable> *tmp = node;
                node = node->left;
                delete tmp;
            }
            
            if (node->right != nullptr) {
                AvlNode<Comparable> *tmp = node;
                node = node->right;
                delete tmp;
            }
        }
        
    }
}
template <typename Comparable>
AvlNode<Comparable> * & AVLTree<Comparable>::constainsAtNode(const Comparable & x, AvlNode<Comparable> * & t) const {
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
bool AVLTree<Comparable>::contains(const Comparable & x, AvlNode<Comparable> * t) const {
    return constainsAtNode(x, t) != nullptr;
}

template <typename Comparable>
void AVLTree<Comparable>::printTree(AvlNode<Comparable> * t, std::ostream & cout) const {
    cout << "[ ";
    std::stack<AvlNode<Comparable> *> st;
    if (t != nullptr) {
        st.push(t);
    } else {
        cout << "null_root]";
    }
    while (!st.empty()) {
        AvlNode<Comparable> *top = st.top();
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
AvlNode<Comparable> * AVLTree<Comparable>::clone(AvlNode<Comparable> * t) const {
    if (t == nullptr) return nullptr;
    AvlNode<Comparable> * node = new AvlNode<Comparable>(t->m_element,t->left,t->right);
    node->left = clone(t->left);
    node->right = clone(t->right);
    return node;
}

template <typename Comparable>
void AVLTree<Comparable>::clear(AvlNode<Comparable> * & t) {
    if (t != nullptr) {
        clear(t->left);
        clear(t->right);
        delete t;
    }
    t = nullptr;
}
