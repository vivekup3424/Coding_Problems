#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countTriangles(vector<int> &arr) {
        sort(arr.begin(), arr.end());
        int n = arr.size();
        int count = 0;
        for (int k = n - 1; k >= 2; k--) {
            int i = 0, j = k - 1;
            while (i < j) {
                if (arr[i] + arr[j] > arr[k]) {
                    count += j - i;
                    j--;
                } else {
                    i++;
                }
            }
        }
        return count;
    }
};
