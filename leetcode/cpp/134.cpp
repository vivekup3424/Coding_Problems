
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();
        int start = 0;
        for (int i = 0; i < n; i++)
        {
            if (gas[i] >= cost[i])
            {
                start = i;
            }
        }
        int temp = start;
        int i = 0;
        while (i < n)
        {
            int res = gas[start] - cost[i];
            if (res <= 0)
            {
                start = (start + 1) % n;
                i++;
            }
            else
            {
                return -1;
            }
        }
        return temp + 1;
    }
};
int main()
{
}