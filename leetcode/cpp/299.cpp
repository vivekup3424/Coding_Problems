#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string getHint(string secret, string guess)
    {
        int n = secret.size();
        vector<bool> visited(n, false);
        // count the number of bulls
        int bulls = 0, cows = 0;
        for (int i = 0; i < n; i++)
        {
            if (secret[i] == guess[i])
            {
                bulls++;
                visited[i] = true;
            }
        }
        set<int> extras for (int i = 0; i < n; i++)
        {
            if (visited[i] == false)
            {
            }
        }
    }
};