// Given a sequence of matrices, find the most efficient way to multiply these matrices together.
// The problem is not actually to  perform the multiplications,
// but merely to decide in which order to perform the multiplications.
#include <bits/stdc++.h>
using namespace std;

// Steps
// 1.Find i and j value
// 2.Find right base condition
// 3.Move k->i to j (find k loop scheme)
// 4.Calculate answer from temporary answer
int solve(vector<int> arr, int i, int j)
{
    int t[i + 1][j + 1];
    memset(t, -1, (i + 1) * (j + 1));
    if (t[i][j] != -1)
        return t[i][j];
    else if (i >= j)
    {
        return t[i][j] = 0;
    }
    else if (i == 0 or j >= arr.size() - 1)
    {
        return t[i][j] = 0;
    }
}