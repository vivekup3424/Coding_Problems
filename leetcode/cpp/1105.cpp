#include <bits/stdc++.h>
using namespace std;
/*
f(i,remainingShelfWidth,maxHeight)=min(maxHeight+f(i+1,shelfWidth−books[i][0],books[i][1]),f(i+1,remainingShelfWidth−books[i][0],max(maxHeight,books[i][1])))
*/
class Solution
{
public:
    int recurse(vector<vector<int>> &books, int shelfWidth, int i, int remainingShelfWidth, int maxHeight)
    {
        if (i == books.size() - 1)
        {
            if (remainingShelfWidth - books[i - 1][0] < 0)
            {
                return maxHeight + books[i][1];
            }
            else
            {
                return max(maxHeight, books[i][0]);
            }
        }
        else
        {
            return min(
                maxHeight + recurse(books, shelfWidth, i + 1, shelfWidth - books[i][0], books[i][1]),
                recurse(books, shelfWidth, i + 1, remainingShelfWidth - books[i][0], max(maxHeight, books[i][1])));
        }
    }
    int bottomup(vector<vector<int>> &books, int sheldWidth)
    {
        int n = books.size();
        int dp[n];
        dp[0] = books[i] for (int i = 0; i < n; i++)
        {
        }
    }
    int minHeightShelves(vector<vector<int>> &books, int shelfWidth)
    {
    }
};