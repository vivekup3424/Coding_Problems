#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    double mincostToHireWorkers(vector<int> &quality, vector<int> &wage, int k)
    {
        int n = quality.size();
        // wage/quality
        double min_ratio = INT_MAX;
        int min_index = -1;
        for (int i = 0; i < n; i++)
        {
            double ratio = (double)wage[i] / (double)quality[i];
            cout << "ratio i:" << i << " => " << ratio << endl;
            if (ratio < min_ratio)
            {
                min_ratio = ratio;
                min_index = i;
            }
        }
        return 0;
    }
};
int main()
{
    vector<int> quality = {10, 20, 5};
    vector<int> wage = {70, 50, 30};
    Solution A;
    A.mincostToHireWorkers(quality, wage, 2);
}