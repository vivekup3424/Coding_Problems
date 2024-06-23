#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Project
{
    int profit;
    int capital;
};

class Solution
{
public:
    int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital)
    {
        int n = profits.size();
        vector<Project> projects;

        // Creating a vector of Project structs
        for (int i = 0; i < n; i++)
        {
            projects.push_back({profits[i], capital[i]});
        }

        // Sorting projects by their capital requirements
        sort(projects.begin(), projects.end(), [](const Project &a, const Project &b)
             { return a.capital < b.capital; });

        // Using a max heap to keep track of the most profitable projects that can be taken
        priority_queue<int> maxHeap;
        int index = 0;

        // Selecting at most k projects
        for (int i = 0; i < k; i++)
        {
            // Adding all projects that can be taken with the current capital to the max heap
            while (index < n && projects[index].capital <= w)
            {
                maxHeap.push(projects[index].profit);
                index++;
            }

            // If there are no projects that can be taken, break out of the loop
            if (maxHeap.empty())
                break;

            // Take the most profitable project
            w += maxHeap.top();
            maxHeap.pop();
        }

        return w;
    }
};
