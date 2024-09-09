#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution
{
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode *head)
    {
        int left_col = 0, right_col = n - 1,
            top_row = 0, bottom_row = m - 1;
        vector<vector<int>> ans(m, vector<int>(n, -1));
        ListNode *temp = head;
        while (left_col <= right_col || top_row <= bottom_row)
        {
            for (int j = left_col; j <= right_col; j++)
            {
                if (temp != nullptr)
                {
                    ans[top_row][j] = temp->val;
                    temp = temp->next;
                }
                else
                {
                    ans[top_row][j] = -1;
                }
            }
            top_row++;
            for (int i = top_row; i <= bottom_row; i++)
            {
                if (temp != nullptr)
                {
                    ans[i][right_col] = temp->val;
                    temp = temp->next;
                }
                else
                {
                    ans[i][right_col] = -1;
                }
            }
            right_col--;
            for (int j = right_col; j >= left_col; j--)
            {
                if (temp != nullptr)
                {
                    ans[bottom_row][j] = temp->val;
                    temp = temp->next;
                }
                else
                {
                    ans[bottom_row][j] = -1;
                }
            }
            bottom_row--;
            for (int j = bottom_row; j >= top_row; j--)
            {
                if (temp != nullptr)
                {
                    ans[j][left_col] = temp->val;
                    temp = temp->next;
                }
                else
                {
                    ans[j][left_col] = -1;
                }
            }
            left_col++;
        }
        return ans;
    }
};