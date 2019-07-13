//
//  main.cpp
//  vector_binarySearch
//
//  Created by SteveLin on 2019/7/9.
//  Copyright © 2019 alin. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
static int const NOT_FOUND = -1;
template <class Comparable>
int binarySearch(const vector<Comparable> &vec, int x) {
    int low = 0;
    int high = (int)vec.size() - 1;
    
    while (low <= high) {
        int mid = (low + high) / 2;
        if (vec[mid] < x) {
            low = mid + 1;
        } else if (vec[mid] > x) {
            high = mid - 1;
        } else {
            return mid;
        }
    }
    return NOT_FOUND;
}

int main(int argc, const char * argv[]) {
    int ia[12] = {1,2,4,6,19,10,44,66,55,77,88,99};
    vector<int> vec = vector<int>(ia,ia+12);
    int search_value = 44;
    int index = binarySearch<int>(vec, search_value);
    cout << "index = " << index << endl;
    cout << "vec["<< index << "] = " << vec[index] << endl;
    cout << "search_value = " << search_value<< endl;
    return 0;
}
