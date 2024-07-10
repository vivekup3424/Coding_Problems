#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &i : a)
    {
        cin >> i;
    }
    int sum = accumulate(a.begin(), a.end(), 0);
    vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));
    set<int> sums; // To store the sums that can be formed
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < sum + 1; j++)
        {
            if (j == 0)
            {
                dp[i][j] = true;
            }
            else if (i == 0)
            {
                dp[i][j] = false;
            }
            else if (j >= a[i - 1])
            {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - a[i - 1]];
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
            if (dp[i][j] and j != 0)
            {
                sums.insert(j);
            }
        }
    }
    cout << sums.size() << endl;
    for (int i : sums)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
