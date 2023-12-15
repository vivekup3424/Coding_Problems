// Minimum number of jumps to reach end
// | Set 2 (O(n) solution)

// Given an array of integers where each element represents the
// max number of steps that can be made forward from that element.
// Write a function to return the minimum number of jumps to reach
// the end of the array (starting from the first element).
// If an element is 0, then we cannot move through that element.
// If we can’t reach the end, return -1

// Solution
// https://www.geeksforgeeks.org/minimum-number-jumps-reach-endset-2on-solution/
#include <bits/stdc++.h>
using namespace std;

int max(int A, int B)
{
    if (A >= B)
        return A;
    else
        return B;
}

// Returns the minimum number of jumps to go from start to finish
int minJumps(vector<int> v, int length)
{
    // no of jumps required to reach end = 0
    if (length == 1)
        return 1;

    // return -1 if not possible to jump
    else if (v[0] == 0)
        return -1;
}