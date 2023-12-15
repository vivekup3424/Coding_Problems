// Given a set of integers, the task is to divide it into two sets S1 and S2 such that the
// absolute difference between their sums is minimum.

// Recursive Solution :
// The recursive approach is to generate all possible sums from all the values of the
// array and to check which solution is the most optimal one.To generate sums we
// either include the i’th item in set 1 or don’t include, i.e., include in set 2.

#include <bits/stdc++.h>
using namespace std;

// verifies whether the set has following subset sum present
bool is_subset_sum(vector<int> v, int n, int subset_sum) // n is no of element from {1,2,3...n-1}
{
    if (subset_sum == 0)
        return true;
    else if (n == 0)
        return false;
    else
    {
        return is_subset_sum(v, n - 1, subset_sum - v[n - 1]) || is_subset_sum(v, n - 1, subset_sum);
    }
}

// S1 ranges from (0,range/2)
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