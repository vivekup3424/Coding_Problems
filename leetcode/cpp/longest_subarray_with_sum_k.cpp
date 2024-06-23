#include <bits/stdc++.h>
using namespace std;

int longestSubarrayWithSumK_1(vector<int> a, long long k) // prefix-sum-hashing for +ve integer array //important question,asked in google
{
    // this code will fail on the edgecase in which array contains 0
    map<long long, int> prefSumMap; // stores the prefix sum for each index
    long long sum = 0;
    int maxLen = 0;
    for (int i = 0; i < a.size(); i++)
    {
        sum += a[i];
        if (sum == k)
        {
            maxLen = max(maxLen, i + 1);
        }
        int remaining_sum = sum - k;
        if (prefSumMap.find(remaining_sum) != prefSumMap.end())
        {
            int len = i - prefSumMap[remaining_sum];
            maxLen = max(maxLen, len);
        }
        prefSumMap[sum] = i;
    }
    return maxLen;
}

// since the above code won't work
// because it this cause updating the value that has already been updated
int longestSubarrayWithSumK_2(vector<int> a, long long k) // prefix-sum-hashing for +ve integer array //important question,asked in google
{
    map<long long, int> prefSumMap; // stores the prefix sum for each index
    long long sum = 0;
    int maxLen = 0;
    for (int i = 0; i < a.size(); i++)
    {
        sum += a[i];
        if (sum == k)
        {
            maxLen = max(maxLen, i + 1);
        }
        int remaining_sum = sum - k;
        if (prefSumMap.find(remaining_sum) != prefSumMap.end())
        {
            int len = i - prefSumMap[remaining_sum];
            maxLen = max(maxLen, len);
        }
        // this code takes into account the edge where we have 0 in ou array
        if (prefSumMap.find(sum) == prefSumMap.end())
        {
            prefSumMap[sum] = i;
        }
    }
    return maxLen;
    // this above code can also work if we have some negatives
    // Time Complexity = O(nlogn)
    // Space Complexity = O(n)
}
// https://www.codingninjas.com/studio/problems/longest-subarray-with-sum-k_5713505?utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_Arrayproblems

//  now after giving a better solution, we need to think about the optimal solution
//  for array containing only positive and zero integers
//  https://www.codingninjas.com/studio/problems/longest-subarray-with-sum-k_6682399?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf&leftPanelTab=0

int main()
{
}