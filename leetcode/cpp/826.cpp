#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Job
{
    int profit;
    int difficulty;
};

class Solution
{
public:
    // Comparator for the priority_queue
    struct JobComparator
    {
        bool operator()(const Job &a, const Job &b)
        {
            return a.profit < b.profit; // Max heap for profit
        }
    };

    int maxProfitAssignment(vector<int> &difficulty, vector<int> &profit, vector<int> &worker)
    {
        int n = profit.size(), m = worker.size();

        // Create a vector of jobs and sort by difficulty
        vector<Job> jobs(n);
        for (int i = 0; i < n; i++)
        {
            jobs[i] = {profit[i], difficulty[i]};
        }
        sort(jobs.begin(), jobs.end(), [](const Job &a, const Job &b)
             { return a.difficulty < b.difficulty; });

        // Sort workers by ability
        sort(worker.begin(), worker.end());

        // Max heap for the best available job
        priority_queue<Job, vector<Job>, JobComparator> maxHeap;
        int total = 0, j = 0;

        // Iterate through each worker
        for (int i = 0; i < m; i++)
        {
            // Add all jobs the current worker can do to the maxHeap
            while (j < n && jobs[j].difficulty <= worker[i])
            {
                maxHeap.push(jobs[j]);
                j++;
            }

            // If there are available jobs, assign the best one to the current worker
            if (!maxHeap.empty())
            {
                total += maxHeap.top().profit;
            }
        }

        return total;
    }
};

int main()
{
    Solution solution;
    vector<int> difficulty = {2, 4, 6, 8, 10};
    vector<int> profit = {10, 20, 30, 40, 50};
    vector<int> worker = {4, 5, 6, 7};

    int maxProfit = solution.maxProfitAssignment(difficulty, profit, worker);
    cout << "Max Profit: " << maxProfit << endl;

    return 0;
}
