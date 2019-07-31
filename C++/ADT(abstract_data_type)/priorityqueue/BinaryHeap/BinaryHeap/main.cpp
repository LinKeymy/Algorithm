//
//  main.cpp
//  BinaryHeap
//
//  Created by SteveLin on 2019/7/25.
//  Copyright © 2019 SteveLin. All rights reserved.
//

#include <iostream>
#include "BinaryHeap.cpp"

int main(int argc, const char * argv[]) {
//    BinaryHeap<int> heap;
     vector<int> v = {81,94,11,96,12,35,17,95,28,58,41,75,15};
//    vector<int> items = {150,80,40,30,10,50,110,100,20,90,60,70,120,140,130};
    BinaryHeap<int> heap(v);
//
//    heap.printHeap();
//    heap.deleteMin();
//    heap.printHeap();
    return 0;
}
