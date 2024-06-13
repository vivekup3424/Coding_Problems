// Given an array Arr[] and a difference diff, find the number of subsets that
// array can be divided so that each the difference between the two subset is the given diff.

// S = {a1,a2,a3,a4,..an}
// S1-S2 = (a1+a3+a5+...an-1)-(a2+a4+a6...+an) = diff
//=>S1 - (Range-S1) = diff => Range - 2*S1 = diff
// S1 = (Range - diff)/2
//=> we can use the count subset sum solution to find the num of subset with the given sum
// belongs to the sum or not

#include <bits/stdc++.h>
using namespace std;
int count_subsets(vector<int> v, int n, int subset_sum)
{
    // int t[n + 1][subset_sum + 1];
    // memset(t, -1, (n + 1) * (subset_sum + 1));
    if (subset_sum == 0)
        return 1;
    else if (n == 0)
        return 0;
    else if (v[n - 1] > subset_sum) // if element > subset_sum, don't include it
    {
        return count_subsets(v, n - 1, subset_sum);
    }
    else if (v[n - 1] <= subset_sum) // have a choice diagram
    {
        return count_subsets(v, n - 1, subset_sum - v[n - 1]) + count_subsets(v, n - 1, subset_sum);
    }
}
int num_of_subset_pair(vector<int> v, int diff)
{
    int sum = 0;
    for (int i = 0; i < v.size(); i++)
    {
        sum += v[i];
    }
    int s1 = (sum - diff) / 2; // subset 1
    // am i overcounting s1?

    // no
    int num_pairs = count_subsets(v, v.size(), s1);
    return num_pairs;
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    int num_pairs = num_of_subset_pair(v, k); // k is the differnce
    cout << num_pairs << "\n";
}
// Time complexity = O(n^2);
