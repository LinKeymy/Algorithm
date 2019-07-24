//
//  main.cpp
//  AVLTree
//
//  Created by SteveLin on 2019/7/23.
//  Copyright © 2019 unixlin. All rights reserved.
//

#include <iostream>

#include "AVLTree.h"

int main(int argc, const char * argv[]) {
    
    AVLTree<int> avl;
    avl.insert(3);
    avl.insert(2);
    avl.insert(1);
    avl.insert(4);
    avl.insert(5);
    avl.insert(6);
    avl.insert(7);
    avl.insert(16);
    avl.insert(15);
    avl.insert(14);
    avl.insert(13);
    avl.insert(12);
    avl.insert(11);
    avl.insert(10);
    avl.insert(8);
    avl.insert(9);
    avl.levelorderTraversal();
    
    return 0;
}
