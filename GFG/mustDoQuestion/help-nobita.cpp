#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string oddEven(string s)
{
    map<char, int> freq;
    ll sum = 0;
    for (char c : s)
    {
        freq[c]++;
    }
    for (auto it : freq)
    {
        int c = int(it.first - 'a');
        int f = it.second;
        if (c % 2 == 0 and f % 2 == 1)
        {
            sum += f;
        }
        else if (c % 2 == 1 and f % 2 == 0)
        {
            sum += f;
        }
    }
    return (sum % 2 == 1 ? "ODD" : "EVEN");
}
int main()
{
    string s = "bddvpw";
    cout << oddEven(s);
}