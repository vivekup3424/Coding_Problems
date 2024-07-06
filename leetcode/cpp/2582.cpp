#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution
{
public:
    int passThePillow(int n, int time)
    {
        int position = 1;
        bool right = true;
        while (time)
        {
            if (right)
            {
                position++;
                if (position == n)
                {
                    right = false;
                }
            }
            else
            {
                position--;
                if (position == 1)
                {
                    right = true;
                }
            }
            time--;
        }
        return position;
    }
};