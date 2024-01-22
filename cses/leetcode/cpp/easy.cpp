#include <bits/stdc++.h>
using namespace std;
vector<vector<long long>> teams(long long L, long long R)
{
    // since we have even number of member in the range n = R-L+1
    // hence we can say that n/2 will be odd ID and n/2 will be even IDs
    // hence pair every odd ID will even ID, using odd and even pointers'
    //=>2-pointer approach
    long long i = L, j = R;
    vector<vector<long long>> ans;
    while (i < j)
    {
        ans.push_back({i++, j--});
    }
    return ans;
}

int main()
{
    long long L = 1;
    long long R = 8;
    vector<vector<long long>> v;
    v = teams(L, R);
}