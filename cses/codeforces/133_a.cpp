
#include <bits/stdc++.h>
using namespace std;

int main()
{
    unordered_set<char> st = {'H', 'Q', '9'};
    string s;
    cin >> s;
    for (char c : s)
    {
        if (st.count(c))
        {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}