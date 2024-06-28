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
// using an ordering
bool ascendingEndingTimes(int a[2], int b[2])
{
    if (a[1] < b[1])
    {
        return true;
    }
    else if (a[0] < b[0])
    {
        return true; // sort in increasing order of starttime
    }
    else
    {
        return false;
    }
}
int minHallsOrdering(int lectures[][2], int n)
{
    sort(lectures, lectures + n, ascendingEndingTimes);
    int count = 0;
    int end_time = -1;
    for (int i = 0; i < n; i++)
    {
        if (lectures[i][0] > end_time)
        {
            // current meeting takes place after, the
            // previous meeting has been held
            end_time = lectures[i][0];
        }
        else if (lectures[i][0] <= end_time)
        {
            // current meeting takes place before the previous
            // meeting has been adjourned
            // hence new room is required
            count++;
            end_time = max(end_time, lectures[i][1]);
        }
    }
}