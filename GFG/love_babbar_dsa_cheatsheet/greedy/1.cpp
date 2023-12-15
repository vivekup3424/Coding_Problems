// Activity Selection Problem

// You are given n activities with their start and finish times.
// Select the maximum number of activities that can be performed by
// a single person, assuming that a person can only work on a single activity at a time.

#include <bits/stdc++.h>
using namespace std;

void printMaxActivities(vector<int> s, vector<int> f, int n)
{
    vector<pair<int, int>> f_ss;
    for (int i = 0; i < n; i++)
    {
        pair<int, int> f_s = {f[i], s[i]};
        f_ss.push_back(f_s);
    }
    sort(f_ss.begin(), f_ss.end());
    int activity_counter = 0;
    vector<int> index_of_selected_activity;
    int i = 0;
    index_of_selected_activity.push_back(i);
    for (int j = 0; j < n; j++)
    {
        if (f_ss[j].second >= f_ss[i].first)
        {
            index_of_selected_activity.push_back(j);
            i = j;
        }
    }
    cout << "Start_Time\tFinish_Time\n";
    for (int i = 0; i < index_of_selected_activity.size(); i++)
    {
        cout << f_ss[index_of_selected_activity[i]].second << "\t" << f_ss[index_of_selected_activity[i]].first << endl;
    }
} // Driver code
int main()
{
    vector<int> s = {1, 3, 0, 5, 8, 5};
    vector<int> f = {2, 4, 6, 7, 9, 9};
    int n = sizeof(s) / sizeof(s[0]);

    // Function call
    printMaxActivities(s, f, n);
    return 0;
}

// this same code can be implemented by using a priority-queue in place
//  of vector, hence in that case there would be no need for sorting the input