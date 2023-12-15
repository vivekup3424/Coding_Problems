
#include <bits/stdc++.h>
using namespace std;
int minimumCost(int n, int x, int y, string &s)
{
    unordered_set<char> st = {'a', 'e', 'i', 'o', 'u'};
    int num_vowels = 0, num_const = 0;
    for (char c : s)
    {
        if (st.count(c) == 0)
        {
            num_const++;
        }
        else
        {
            num_vowels++;
        }
    }
    int a = (n - num_vowels) * x;
    int b = (n - num_const) * y;
    return min(a, b);
}
int main()
{
    int n = 6;
    string s = "xafezn";
    int x = 4, y = 8;
    int b = minimumCost(n, x, y, s);
    return 0;
}