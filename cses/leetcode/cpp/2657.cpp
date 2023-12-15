
#include <bits/stdc++.h>
using namespace std;

// Failed Solution
class Solution
{
public:
    vector<int> findThePrefixCommonArray(vector<int> &A, vector<int> &B)
    {
        set<int> a, b;
        int n = A.size();
        vector<int> ans(n, 0);
        for (int i = 0; i < n; i++)
        {
            a.insert(A[i]);
            b.insert(B[i]);

            if (a == b)
            {
                if (i != 0)
                    ans[i] = a.size();
                else
                    ans[i] = 1;
            }
            else
            {
                if (i != 0)
                    ans[i] = ans[i - 1];
                else
                    ans[i] = 0;
            }
        }
        return ans;
    }
};

class Solution1
{
public:
    vector<int> findThePrefixCommonArray(vector<int> &A, vector<int> &B)
    {
    }
};
int main()
{
    Solution S;
    vector<int> A = {1, 2, 3, 4};
    vector<int> B = {3, 1, 2, 4};
    vector<int> R = S.findThePrefixCommonArray(A, B);
    for (auto x : R)
    {
        cout << x << " ";
    }
    cout << endl;
}
