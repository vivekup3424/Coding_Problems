#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> partitionLabels(string s)
{
    map<char, vector<int>> indices;
    // getting all the indices
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        indices[s[i]].push_back(i);
    }
    int start = 0, end = 0;
    vector<int> ans;
    while (end < n)
    {
        set<char> st;
        if (start == end)
        {
            st.insert(s[end]);
            end = max(end, indices[s[end]].back());
            // get all the elements in the range
            for (int i = start; i <= end; i++)
            {
                st.insert(s[i]);
                end = max(end, indices[s[i]].back());
            }
        }
        ans.push_back(end - start + 1);
        end = end + 1;
        start = end;
    }
    return ans;
}