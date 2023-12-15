
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool canPlaceFlowers(vector<int> &f, int n)
    {
        int counter = 0;
        if (f[0] == 0 and f[1] == 0)
        {
            f[0] == 1;
            counter++;
        }
        if (f[n - 2] == 0 and f[n - 1] == 0)
        {
            f[n - 1] == 1;
            counter++;
        }
        for (int i = 1; i < n - 2; i++)
        {
            if (f[i - 1] == 0 and f[i] == 0 and f[i + 1] == 0)
                counter++;
        }
        if (counter >= n)
            return true;
        return false;
    }
};
int main()
{
}