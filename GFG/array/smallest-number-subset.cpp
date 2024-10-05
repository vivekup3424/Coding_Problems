#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long findSmallest(vector<int> &arr)
    {
        long long int res = 1;
        int n = arr.size();
        sort(arr.begin(), arr.end());
        for (int i = 0; i < n && arr[i] <= res; i++)
            res = res + arr[i];

        return res;
    }
};