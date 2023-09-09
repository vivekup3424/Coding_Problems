
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int bestClosingTime(string cus)
    {
        int count = 0, mc = 0, mi = 0;
        for (int i = 0; i < cus.size(); i++)
        {
            if (cus[i] == 'Y')
            {
                count++;
            }
            else
                count--;
            if (count > mc)
            {
                mc = count;
                mi = i;
            }
        }
        return mi;
    }
};
int main()
{
    string c = "YYNY";
    Solution s;
    cout << s.bestClosingTime(c) << endl;
}