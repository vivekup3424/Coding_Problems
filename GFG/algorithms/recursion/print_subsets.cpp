// print all the subset of a given set

#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> subsets;
void generate_subset(vector<int> &subset, int i, vector<int> &s) // whether to choose the ith index
{
    if (i == s.size())
    {
        subsets.push_back(subset);
        return;
    }
    subset.push_back(s[i]);
    generate_subset(subset, i + 1, s);
    subset.pop_back();
    generate_subset(subset, i + 1, s);
}
int main()
{
    vector<int> s = {1, 2, 3, 4, 5};
    vector<int> empty;
    generate_subset(empty, 0, s);
    for (auto subset : subsets)
    {
        for (auto element : subset)
        {
            cout << element << ", ";
        }
        cout << "\n";
    }
}