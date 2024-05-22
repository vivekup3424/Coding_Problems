#include <bits/stdc++.h>
using namespace std;

/**
 *Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.
 */

// Case-1
// When length of array <= 1e5
// Use the concept of prefix computation
int minHalls(int lectures[][2], int n)
{

    // Initialize a vector of pair, Time, first value
    // indicates the time of entry or exit of a lecture
    // second value denotes whether the lecture starts or
    // ends
    vector<pair<int, int>> Time;

    // Store the lecture times
    for (int i = 0; i < n; i++)
    {
        Time.push_back({lectures[i][0], 1});
        Time.push_back({lectures[i][1] + 1, -1});
    }

    // Sort the vector
    sort(Time.begin(), Time.end());

    int answer = 0, sum = 0;

    // Traverse the Time vector and Update sum and answer
    // variables
    for (int i = 0; i < Time.size(); i++)
    {
        sum += Time[i].second;
        answer = max(answer, sum);
    }

    // Return the answer
    return answer;
}

// Case-II
// when n >=1e9
// we can't use the above approach
// but we can think in terms of getting the
// maximum number of non-overlapping intervals
// using a priority-queue I can solve this question
