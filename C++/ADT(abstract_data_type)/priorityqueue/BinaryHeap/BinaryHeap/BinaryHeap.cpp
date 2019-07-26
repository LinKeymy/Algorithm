//
//  BinaryHeap.cpp
//  BinaryHeap
//
//  Created by SteveLin on 2019/7/25.
//  Copyright © 2019 SteveLin. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

template <typename Comparable>
class BinaryHeap {
    
    
public:
    explicit BinaryHeap(int capacity = 100):array(capacity) {
        
    }
    // 先将元素都拷贝至array，然后处理堆序性质
    explicit BinaryHeap(const vector<Comparable> & items): array(items.size() + 10),currentSize((int)items.size()) {
        for (int i = 0; i < currentSize; ++i) {
            array[i + 1] = items[i];
        }
        buildHeap();
    }
    
    bool isEmpty() {
        return currentSize == 0;
    }
    
    const Comparable & findMin() const {
        return array[1];
    }
    
    /*
     index 0    1   2   3   4   5 .....
     item       a   b   c   d   e .....
     */
    void insert(const Comparable & x) {
        
        if (currentSize == array.size() - 1) { // 下标 1 开始存放
            array.resize(array.size() * 2); // 扩容
        }
        
        int hole = ++currentSize;
        Comparable copy = x; // Comparable copy constructor will call
        array[0] = move(copy);
        for (; x < array[ hole / 2 ]; hole /= 2) { // 当hole == 1 时，
            // hole 上移确定位置。然后在进行赋值操作，这样可以将 3po 的赋值cutdown到 po + 1 次
            array[hole] = move(array[ hole / 2 ]); // percolate up
        }
        // 不能move x，这样会修改x，copy已经被move到array[0]，这点要注意
        array[hole] = move(array[0]);
    }
    void insert(Comparable && x) {
        
        if (currentSize == array.size() - 1) {
            array.resize(array.size() * 2);
        }
        
        int hole = ++currentSize;
        array[0] = move(x);
        
        for (; array[0] < array[ hole / 2 ]; hole /= 2) {
            array[hole] = move(array[ hole / 2 ]);
        }
        array[hole] = move(array[0]);
    }
    
    void deleteMin() {
        if (isEmpty()) {
            throw underflow_error("delete emtpy head is wrong");
        }
        array[1] = move(array[currentSize--]);
        percolateDown(1);
    }
    
    
    void deleteMin(Comparable & minItem) {
        if (isEmpty()) {
            throw underflow_error("delete emtpy head is wrong");
        }
        minItem = move(array[1]);
        array[1] = move(array[currentSize--]);
        percolateDown(1);
    }
    
    void clear() {
        currentSize = 0;
    }
    
    void printHeap() {
        cout << "[ ";
        for (int i = 1; i <= currentSize; i *= 2) {
            cout << "[ ";
            for (int j = i; j < i * 2 ; ++j) {
                if (j > currentSize ) break;
                cout << array[j] << " ";
            }
            cout << " ]";
        }
        cout << " ]" << endl;
    }
    

private:
    int currentSize;
    vector<Comparable> array;
    
    void buildHeap() {
        // int i = currentSize / 2 为倒数第二层的最后一个节点，右->左 ， 下->上进行percolate down
        for (int i = currentSize / 2; i > 0; --i) {
            percolateDown(i);
        }
    }
    void percolateDown(int hole) {
        int child;
        Comparable tmp = move(array[hole]);
        for (; hole * 2 <= currentSize; hole = child) {
            child = 2 * hole;
            // 判断hole时应该下移到那个child，如果是右儿子，那么执行 ++ child， 否则 child 不变。
            // 如果 child == currentSize，那么child是最后一个节点，而且是左节点，这个时候也就不用考虑右儿子了
            // 如果 child != currentSize，那么child不是最后一个节点。
            if (child != currentSize && array[child + 1] < array[child]) {
                ++child;
            }
            if (array[child] < tmp) {  // 如果hole比小儿子大，hole那么percolateDown，小儿子上去
                array[hole] = move(array[child]);
            } else {
                break;  // 如果hole比小儿子小，那么可以将删除前的最后一个项放在该hole中，也就是tmp
            }
        }
        array[hole] = move(tmp);
    }
    
    
};
