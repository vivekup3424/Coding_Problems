// Sum of subset differences
//     Given a set of integers,
//     the task is to divide it into two sets S1 and S2 such that the absolute difference
//     between their sums is minimum.If there is a set S with n elements, then if we assume
//     Subset1 has m elements, Subset2 must have n - m elements and the value of
//     abs(sum(Subset1) – sum(Subset2)) should be minimum.

#include <bits/stdc++.h>
using namespace std;
#define MAX 100
int t[MAX + 1][MAX + 1];

// returns the minimum difference between the sum of complementary subsets
int minimum_difference(vector<int> v)
{
}