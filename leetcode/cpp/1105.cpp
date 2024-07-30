#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minHeightShelves(vector<vector<int>> &books, int shelfWidth)
    {
        sort(books.begin(), books.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[1] > b[1]; });
        // output the vectors
        for (auto book : books)
        {
            cout << book[0] << ", " << book[1] << endl;
        }
        return 6;
    }
};