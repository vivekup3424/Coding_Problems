
#include <bits/stdc++.h>
using namespace std;
// Method 1 - Using sorting
class Solution1
{
public:
    vector<int> kWeakestRows(vector<vector<int>> &mat, int k)
    {
        vector<pair<int, int>> v; // a = no of soldiers, b = index
        for (int i = 0; i < mat.size(); i++)
        {
            pair<int, int> p;
            int sum = 0;
            int j = 0;
            while (mat[i][j] != 0 or j < mat[i].size())
            {
                sum++;
                j++;
            }
            p.first = sum;
            p.second = i;
            v.push_back(p);
        }
        sort(v.begin(), v.end());
        vector<int> ans(k);
        for (int i = 0; i < k; i++)
        {
            ans[i] = v[i].second;
        }
        return ans;
    }
};

// counting the number of soldiers in a optimizied way using binary search
int countSoldiers(vector<int> &row)
{
    int left = 0, right = row.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (row[mid] == 1)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return left;
}
class Solution
{
public:
    vector<int> kWeasetRows(vector<vector<int>> &mat, int k)
    {
        priority_queue<pair<int, int>> maxHeap; //(number of soldiers and index)
        for (int i = 0; i < mat.size(); i++)
        {
            int numSoldiers = countSoldiers(mat[i]);
            maxHeap.push({numSoldiers, i});
            if (maxHeap.size() > k)
            {
                maxHeap.pop();
            }
                }
        vector<int> result(k);

        while (!maxHeap.empty())
        {
            result[--k] = maxHeap.top().second; // Pop in reverse order
            maxHeap.pop();
        }

        return result;
    }
};
int main()
{
}