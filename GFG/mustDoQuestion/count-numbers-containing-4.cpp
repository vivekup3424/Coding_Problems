#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class Solution
{
public:
    int countNumberswith4(int n)
    {
        int count = 0;
        for (int i = 4; i <= n; i++)
        {
            int j = i;
            while (j > 0)
            {
                if (j % 10 == 4)
                {
                    count++;
                    break;
                }
                j = j / 10;
            }
        }
        return count;
    }
};
int main()
{
    cout << Solution().countNumberswith4(44) << endl;
}