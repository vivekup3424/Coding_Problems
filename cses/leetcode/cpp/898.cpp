#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class Solution1
{
public:
    // simplest approach
    int subarrayBitwiseORs(vector<int> &arr)
    {
        int n = arr.size();
        // generate all subarrays of arr
        set<int> ans;
        for (int i = 0; i < n; i++)
        {
            int temp = 0;
            for (int j = i; j < n; j++)
            {
                temp = temp | arr[j];
                ans.insert(temp);
            }
        }
        return ans.size();
    }
};
int subarrayBitwiseORs2(vector<int> &arr)
{
    // since there are 4*1e8 elements, hence maximum bit required is 30
    // so our solution can be optimised for that
    set<int> allResults, currentResults, prevResults;
    for (int num : arr)
    {
        for (auto r : prevResults)
        {
            int value = r | num;
            currentResults.insert(value);
        }
        currentResults.insert(num);
        prevResults = currentResults;
        for (auto r : prevResults)
        {
            allResults.insert(r);
        }
    }
    return allResults.size();
}
int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // int n;
    // cin >> n;
    // vector<int> arr(n);
    // for (int i = 0; i < n; i++)
    //{
    //    cin >> arr[i];
    //}
    vector<int> v = {1, 2, 4};
    subarrayBitwiseORs2(v);
}