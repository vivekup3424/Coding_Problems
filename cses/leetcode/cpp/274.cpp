#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int hIndex(vector<int> &citations)
    {
        sort(citations.begin(), citations.end());
        int n = citations.size();
        if (n & 1)
            return citations[n / 2];
        else
            return (citations[n / 2] + citations[n / 2 + 1]) / 2;
    }
};
int main()
{
}