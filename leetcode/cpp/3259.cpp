#include <bits/stdc++.h>
using namespace std;
long long maxEnergyBoost(vector<int> &A, vector<int> &B)
{
    long long a0 = 0, a1 = 0, a2 = 0, b0 = 0, b1 = 0, b2 = 0, n = A.size();
    for (int i = 0; i < n; i++)
    {
        a2 = A[i] + max(a1, b0);
        b2 = B[i] + max(b1, a0);
        a0 = a1;
        a1 = a2;
        b0 = b1;
        b1 = b2;
    }
    return max(a1, b1);
}