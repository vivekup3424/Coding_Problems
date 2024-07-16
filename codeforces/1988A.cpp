#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int minOperations(int n, int k)
{
    int operations = 0;
    vector<int> dp(n + 1);
    int i = 0;
    while (i < k)
    {
        if (i == 0 || i == 1)
        {
            dp[i] = 0;
        }
        for (int j = 0; j < k; j++)
        {
            if (i + j > 1)
            {
                dp[i + j] = dp[max(0, i - k)] + 1;
            }
        }
        i += k - 1;
    }
    return dp[n];
}

int main()
{
    int t;
    cin >> t;
    vector<int> results;
    for (int i = 0; i < t; ++i)
    {
        int n, k;
        cin >> n >> k;
        if (n == 1)
        {
            results.push_back(0);
        }
        else
        {
            results.push_back(minOperations(n, k));
        }
    }
    for (const auto &result : results)
    {
        cout << result << endl;
    }
    return 0;
}
