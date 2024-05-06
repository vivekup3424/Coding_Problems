#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int hash(string s)
    {
        int ans = 0;
        int base = 1;
        for (int i = 0; i < s.size(); i++)
        {
            ans += ans * base + (s[i] - 'a');
            base *= 2;
        }
    }
    int minAnagramLength(string s)
    {
        int n = s.size();
        // getting all possible factors of n
        set<int> factors;
        for (int i = 0; i < sqrt(n); i++)
        {
            if (n % i == 0)
            {
                factors.insert(i);
                factors.insert(i / n);
            }
        }
        // print the factors
        cout << "Factors = " << endl;
        for (auto it : factors)
        {
            cout << it << ", ";
        }
        cout << endl
             << "XXXXXXXXXXXXXXXXXXXXXXX\n";

        // forming the anagrams
        for (auto it : factors)
        {
        }
    }
};
