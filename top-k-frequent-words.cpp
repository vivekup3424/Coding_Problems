#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
using namespace std;

class Comparator {
public:
    bool operator()(const pair<string, int>& a, const pair<string, int>& b) {
        if (a.second == b.second) {
            return a.first > b.first; // minHeap wrt lexicographical order if frequencies are equal
        }
        return a.second < b.second; // maxHeap wrt frequency
    }
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        map<string, int> freq;
        for (auto& word : words) {
            freq[word]++;
        }

        priority_queue<pair<string, int>, vector<pair<string, int>>, Comparator> maxHeap;
        for (auto& it : freq) {
            maxHeap.push({it.first, it.second});
        }

        vector<string> answer;
        while (k-- > 0 && !maxHeap.empty()) {
            answer.push_back(maxHeap.top().first);
            maxHeap.pop();
        }
        return answer;
    }
};
