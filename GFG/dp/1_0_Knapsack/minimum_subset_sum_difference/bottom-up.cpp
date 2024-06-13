// given a set we have to find the minimum difference bet ween the complementary subsets formed
// from this set
#include <bits/stdc++.h>
using namespace std;

bool is_subset_sum(vector<int> v, int n, int subset_sum) // n = no of elements from {1,2,3...n-1}
{
    bool t[n + 1][subset_sum + 1];
    memset(t, -1, (n + 1) * (subset_sum + 1));
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < subset_sum + 1; j++)
        {
            if (j == 0)
                t[i][j] = true;
            else if (i == 0)
                t[i][j] = false;
            else if (v[i - 1] > subset_sum) // don't include it
            {
                t[i][j] = t[i - 1][j];
            }
            else if (v[i - 1] <= subset_sum) // we now have a choice of whether to include the nth element in the subset or not
            {
                t[i][j] = t[i - 1][j - v[i - 1]] || t[i - 1][j]; // include or don't include
            }
        }
    }
    return t[n][subset_sum];
}
int minimum_difference(vector<int> v)
{
    int sum = 0;
    for (int i = 0; i < v.size(); i++)
    {
        sum += v[i];
    }
    int subset_sum = 0;
    for (int i = sum / 2; i >= 0; i++)
    {
        if (is_subset_sum(v, v.size(), i))
        {
            subset_sum = i;
            break;
        }
    }
    return (sum - (2 * subset_sum));
}
int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    int diff = minimum_difference(v);
    cout << diff << "\n";
    return 0;
}