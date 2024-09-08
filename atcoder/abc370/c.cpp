#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    string s, t;
    cin >> s >> t;
    int n = s.size();
    vector<int> priorityIdx;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++)
    {
        if (s[i] != t[i])
        {
            if (t[i] - 'a' < s[i] - 'a')
            {
                priorityIdx.push_back(i);
                visited[i] = true;
            }
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (s[i] != t[i] and visited[i] == false)
        {
            priorityIdx.push_back(i);
            visited[i] = true;
        }
    }
    string temp = s;
    cout << priorityIdx.size() << endl;
    for (int i : priorityIdx)
    {
        temp[i] = t[i];
        cout << temp << endl;
    }

    return 0;
}
