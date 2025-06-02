#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void printVector(vector<int>& v) {
        for (auto i : v) {
            cout << i << "=>";
        }
        cout << endl;
    }
    int candy(vector<int>& ratings) {
        int total_children = ratings.size();
        if (total_children == 0) {
            return 0;
        }
        vector<int> candies(total_children, 1);
        for (int i = 1; i < total_children; i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }
        for (int i = total_children - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            }
        }
        return accumulate(candies.begin(), candies.end(), 0);
    }
};