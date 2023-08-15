
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        int n = ratings.size(), res = 0, min = 0;
        for (int i = 0; i < n; i++)
        {
            if (ratings[i] < min)
            {
                min = ratings[i];
            }
        }
        for (int i = 0; i < n; i++)
        {
            res += ratings[i] - min;
        }
        res += n;
        return res - 1;
    }
};
int main()
{
}