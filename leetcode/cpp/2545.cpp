
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<vector<int>> sortTheStudents(vector<vector<int>> &score, int k)
    {
        int x = score.size();
        int y = score[0].size();

        vector<pair<int, int>> s;
        for (int i = 0; i < x; i++)
        {
            int point = score[i][k - 1];
            s.push_back({point, i});
        }

        sort(s.begin(), s.end(), [](const pair<int, int> &a, const pair<int, int> &b)
             { return a.first < b.first; });

        vector<vector<int>> sortedScore(x, vector<int>(y));
        for (int i = 0; i < x; i++)
        {
            sortedScore[i] = score[s[i].second];
        }

        return sortedScore;
    }
};
int main()
{
}