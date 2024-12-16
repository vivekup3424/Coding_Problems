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
int solve(vector<int> arr, int i, int j) // i = starting index and j = ending index (Ai to Aj)
{
    if (i == j)
    {
        return 0;
    }
    int minimum = INT_MAX;
    // Ai = arr[i-1] x arr[i]
    for (int k = i; k < j; k++)
    {
        // i to k, k+1 to j
        // solve(arr,i,k), solve(arr,k+1,j)

        // arr[i-1*arr[k]*arr[j]
        int temporary = solve(arr, i, k) + solve(arr, k + 1, j) + arr[i - 1] * arr[k] * arr[j];
        minimum = min(minimum, temporary);
    }
    return minimum;
}
int main()
{
    vector<int> arr = {1, 2, 3, 4};
    cout << solve(arr, 0,arr.size()-1);
}
// Time Complexity is exponenetial

//  solve(arr,1,n-1)
