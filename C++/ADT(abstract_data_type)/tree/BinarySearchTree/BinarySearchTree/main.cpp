//
//  main.cpp
//  BinarySearchTree
//
//  Created by SteveLin on 2019/7/20.
//  Copyright © 2019 unixlin. All rights reserved.
//

#include <iostream>
#include "BinarySearchTree.hpp"
using namespace std;
static int ab = 100;
void changeA(int *a) {
    a = &ab;
}

int main(int argc, const char * argv[]) {
    
    

    BinarySearchTree<int> bst;
    bst.insert(7);
    bst.insert(4);
    bst.insert(2);
    bst.insert(1);
    bst.insert(3);
    bst.insert(5);
    bst.insert(9);
    bst.insert(8);
    bst.insert(11);
    bst.insert(10);
    bst.insert(12);
//    cout << bst.findMax() << endl;
//    cout << bst.findMin() << endl;
//    bst.remove(5);
//    bst.remove(6);  // 非元素测试
//    bst.remove(7);
//    bst.remove(9);
//    bst.remove(10);
//    bst.remove(11);
//    bst.clear();
    bst.inorder_traversal_using_stack();
    bst.inorder();
    
//    BinarySearchTree<int> bst1;
//    bst1 = bst;
//    bst.clear();
//    bst.levelorder();
    
//
//    bst.preorder();
////    bst.inorder();
////    bst.postorder();
//    bst.levelorder();
//    bst.reverse();
//    bst.inorder();
////    bst.printTree();
    return 0;
}
