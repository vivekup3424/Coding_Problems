#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // using a hashmap since the elements can be repeated
    void getMinMaxOfSubarrays(vector<int> &v)
    {
        int n = v.size();
        for (int i = 0; i < n; i++)
        {
            map<int, int> hashMapOfSubarray;
            int j = i;
            for (; j < n; j++)
            {
                hashMapOfSubarray[v[j]] += 1;
                printf("Get the max and min from the subarray[%d...%d]\n", i, j);
                printf("Min = %d\n", hashMapOfSubarray.begin()->first);
                printf("Max = %d\n", hashMapOfSubarray.rbegin()->first);
            }
        }
    }
    int getLongestBoundedSubArray(vector<int> v, int k){
        int start = 0, end = 0;
    }
};
int main()
{
    int n;
    cout << "Enter the length of the array:-\n";
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    auto A = Solution();
    A.getMinMaxOfSubarrays(v);
}