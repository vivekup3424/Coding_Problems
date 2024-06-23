
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int timeRequiredToBuy(vector<int> &tickets, int k)
    {
        queue<int> q;
        int n = tickets.size();

        for (int i = 0; i < n; i++)
        {
            q.push(i);
        }

        int seconds = 0;

        while (tickets[k] != 0)
        {
            seconds++;
            int person = q.front();
            q.pop();

            tickets[person]--;

            if (tickets[person] > 0)
            {
                q.push(person);
            }
        }

        return seconds;
    }
};

int main()
{
    vector<int> v = {2, 3, 2};
    int k = 2;
    Solution A = Solution();
    A.timeRequiredToBuy(v, k);
    return 0;
}