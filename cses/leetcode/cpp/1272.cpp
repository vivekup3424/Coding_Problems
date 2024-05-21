/*
1272. Remove Interval
Description

A set of real numbers can be represented as the union of several disjoint intervals, where each interval is in the form [a, b). A real number x is in the set if one of its intervals [a, b) contains x (i.e. a <= x < b).

You are given a sorted list of disjoint intervals intervals representing a set of real numbers as described above, where intervals[i] = [ai, bi] represents the interval [ai, bi). You are also given another interval toBeRemoved.

Return the set of real numbers with the interval toBeRemoved removed
from intervals. In other words, return the set of real numbers such
that every x in the set is in intervals but not in toBeRemoved. Your
answer should be a sorted list of disjoint intervals as described
above.**/
/**
 * Constraints:

    1 <= intervals.length <= 104
    -109 <= ai < bi <= 109
 this means I cannot use a vector (1e9), fuck my life
*/

#include <bits/stdc++.h>
using namespace std;
void findSets(vector<pair<int, int>> sets,
              vector<pair<int, int>> removeIntervals)
{
    sort(sets.begin(), sets.end());
    sort(removeIntervals.begin(), removeIntervals.end());
    vector<pair<int, int>> results;
    // let's make two pointers
    int i = 0, j = 0;
    while (i < sets.size() and j < removeIntervals.size())
    {
        if (sets[i].second > removeIntervals[j].first)
        {
            if (sets[i].first < removeIntervals[j].first)
            {
                results.push_back({sets[i].first,
                                   removeIntervals[j]})
            }
        }
    }
}

int main()
{
    // driver code
    vector<pair<int, int>> sets = {{0, 5}};
    vector<pair<int, int>> removedIntervals = {{2, 3}};
}