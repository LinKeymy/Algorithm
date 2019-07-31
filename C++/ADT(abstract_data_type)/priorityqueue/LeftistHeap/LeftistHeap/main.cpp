//
//  main.cpp
//  LeftistHeap
//
//  Created by SteveLin on 2019/7/27.
//  Copyright © 2019 SteveLin. All rights reserved.
//

#include <iostream>
#include "LeftistHeap.h"


#include <queue>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
using namespace std;



class KthLargest {
    
    priority_queue<int,vector<int>,greater<int>> pq;
    int m_k;
public:
    KthLargest(int k, vector<int>& nums): m_k{ k } {
        for(int i = 0; i < nums.size(); ++i) {
            add1(nums[i]);
        }
    }
    
    void add1(int val) {
        if (pq.size() == m_k) {
            if (val > pq.top()) {
                pq.pop();
                pq.push(val);
            }
        } else {
            pq.push(val);
        }
    }
    
    int add(int val) {
        add1(val);
        return pq.top();
    }
};

class Solution {
public:
    string frequencySort(string s) {
        map<char,int> mp;
        priority_queue<pair<int, char>> pq;
        for (int i = 0; i < s.size(); ++i) {
            ++mp[s[i]];
        }
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            pq.push(make_pair(it->second, it->first));
        }
        s = "";
        while (!pq.empty()) {
            s += string(pq.top().first,pq.top().second);
            pq.pop();
        }
        return s;
    }
};

class Solution1 {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int,int> mp;
        priority_queue<pair<int, int>,vector<pair<int, int>>,greater<pair<int, int>>> pq;
        
        for (int i = 0; i < nums.size(); ++i)
            ++mp[nums[i]];
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            if (pq.size() == k) {
                if (it->second > pq.top().first) {
                    pq.pop();
                    pq.push(make_pair(it->second, it->first));
                }
            } else {
                 pq.push(make_pair(it->second, it->first));
            }
           
        }
        
        vector<int> ans(k);
        for (int i = k; i > 0;) {
            ans[--i] = pq.top().second;
            pq.pop();
        }
        return ans;
    };
};

vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
    sort(points.begin(), points.end(),
         [](const vector<int> &p1, const vector<int> &p2) {
             return p1[0] * p1[0] + p1[1] * p1[1] < p2[0] * p2[0] + p2[1] * p2[1];
         });
    return vector<vector<int>>(points.begin(), points.begin() + K);
}

vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    
    vector<vector<int>> s;
    return s;
};

int main(int argc, const char * argv[]) {
//    Solution1 s;
//    vector<int> v = {1,1,1,2,2,3};
    vector<int> v1 = {1,7,11};
    vector<int> v2 = {2,4,6};
    vector<vector<int>> ans = kSmallestPairs(v1, v2,3);
//    for (auto it = ans.begin(); it != ans.end(); ++it) cout << *it << " " <<  endl;
    return 0;
}
