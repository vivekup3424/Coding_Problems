
#include <bits/stdc++.h>
using namespace std;
class Solution1
{
public:
    int minOperations(vector<int> &nums)
    {
        unordered_map<int, int> freq;
        for (int num : nums)
        {
            if (freq[num] == 0)
            {
                freq[num] = 1;
            }
            else
            {
                freq[num]++;
            }
        }
        int count = 0;
        for (auto it : freq)
        {
            if (it.second % 3 == 0)
            {
                count += it.second / 3;
            }
            else if (it.second % 2 == 0)
            {
                count += it.second / 2;
            }
            else
                return -1;
        }
        return count;
    }
};

class Solution
{
public:
    int minOperations(vector<int> &nums)
    {
        unordered_map<int, int> freq;
        for (int num : nums)
        {
            freq[num]++;
        }

        int count = 0;
        priority_queue<int> pq;
        for (auto it : freq)
        {
            pq.push(it.second);
        }

        while (!pq.empty())
        {
            int x = pq.top();
            pq.pop();
            if (pq.empty())
            {
                count += x;
                break;
            }
            int y = pq.top();
            pq.pop();
            count += (x + y) / 3;
            if ((x + y) % 3 == 1)
            {
                pq.push(1);
            }
            else if ((x + y) % 3 == 2)
            {
                pq.push(2);
            }
        }

        return count;
    }
};
int main()
{
    vector<int> v = {14, 12, 14, 14, 12, 14, 14, 12, 12, 12, 12, 14, 14, 12, 14, 14, 14, 12, 12};
    Solution A = Solution();
    int n = A.minOperations(v);
}