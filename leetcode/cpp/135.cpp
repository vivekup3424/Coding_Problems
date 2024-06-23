
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int candy(vector<int> &r)
    {
        int count = 0;
        int n = r.size();
        if (n == 1)
            return 1;
        vector<int> d(n, 1); // denotes the distribution of candies
        // doing left to right traversal and maintaining the 3rd constraint in right direction
        for (int i = 0; i < n - 1; i++) // go from first to second last element
        {
            if (r[i] < r[i + 1] and d[i + 1] <= d[i])
            {
                d[i + 1] = 1 + d[i];
            }
        }

        // doing right to left traversal and maintaining the 3rd constraint in left constraint
        for (int i = n - 1; i >= 1; i--)
        {
            if (r[i - 1] > r[i] and d[i - 1] <= d[i])
            {
                d[i - 1] = 1 + d[i];
            }
        }
        int sum = 0;
        for (int i : d)
        {
            sum += i;
        }
        return sum;
    }
};
int main()
{
    vector<int> r = {1, 3, 4, 5, 2};
    Solution A;
    int d = A.candy(r);
}