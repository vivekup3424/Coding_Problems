#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string trimZero(const string &s)
{
    int i = 0;
    // Skip leading zeros
    while (i < s.length() && s[i] == '0')
    {
        i++;
    }
    // Append remaining characters
    string temp;
    while (i < s.length())
    {
        temp.push_back(s[i]);
        i++; // Increment i to move to the next character
    }
    return temp;
}

bool containsZero(const string &s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '0')
        {
            return true;
        }
    }
    return false;
}

ll findMinimumResult(const string &s)
{
    if (s.length() <= 2)
    {
        // Return the original value
        ll val = 0;
        for (char c : s)
        {
            val = val * 10 + (c - '0');
        }
        return val;
    }
    // convert s to an set
    set<char> st;
    for (char c : s)
    {
        st.insert(c);
    }
    if (st.size() == 1)
    {
        return s[0] - '0';
    }
    else if (st.size() == 2)
    {
        if (st.find(1) != st.end() and st.find(0) != st.end())
        {
            return 1;
        }
    }
    if (s.size() == 3)
    {
        int sum = 0;
        // get the sum of non-one numbers
        for (char c : s)
        {
            if (c != '1')
            {
                sum += c - '0';
            }
        }
        return sum;
    }
    else if (s.size() > 3 && !containsZero(s))
    {
        // choose the smallest two number from s, and the mark the location visited
        int n = s.size();
        int first = -1, second = -1;
        vector<bool> visited(n);
        int minValue = INT_MAX;
        for (int i = 0; i < n - 1; i++)
        {
            int current_value = (s[i] - '0') * 10 + (s[i + 1] - '0');
            if (minValue > current_value && current_value != 11)
            {
                minValue = current_value;
                first = i;
                second = i + 1;
            }
        }
        visited[first] = true;
        visited[second] = true;
        // now get the sum of rest of the digits, ignoring the
        // places where we have one, and the place where we have visited digits
        int current_sum = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (visited[i] == false && s[i] != '1')
            {
                current_sum += s[i] - '0';
            }
        }
        return current_sum + minValue;
    }
    else
    {
        return 0;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    while (t--)
    {
        int n;
        string s;
        cin >> n >> s;
        s = trimZero(s);
        ll result = findMinimumResult(s);
        cout << result << "\n";
    }

    return 0;
}
