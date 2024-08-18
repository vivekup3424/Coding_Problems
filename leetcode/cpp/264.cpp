#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int nthUglyNumber(int n)
    {
        priority_queue<int, vector<int>, greater<int>> pq;
        pq.push(1);
        set<int> s;
        int number = 1;
        while (s.size() < n)
        {
            number = pq.top();
            s.insert(number);
            pq.pop();
            pq.push(number * 2);
            pq.push(number * 3);
            pq.push(number * 5);
        }
        return number;
    }
};
int main()
{
    int n = 12;
    Solution().nthUglyNumber(n);
}