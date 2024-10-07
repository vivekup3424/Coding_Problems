// Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
#include <bits/stdc++.h>
using namespace std;
// Method 1:- Using backtracking
class Solution1
{
public:
    void dfs(vector<string> &combinations, string &comb, int no_opening, int no_closing)
    {
        if (no_opening == 0 && no_closing == 0)
        {
            combinations.push_back(comb);
            return;
        }
        else
        {
            if (no_opening > 0)
            {
                comb.push_back('(');
                dfs(combinations, comb, no_opening - 1, no_closing);
                comb.pop_back();
            }
            if (no_closing > 0)
            {
                if (no_closing > no_opening)
                {
                    comb.push_back(')');
                    dfs(combinations, comb, no_opening, no_closing - 1);
                    comb.pop_back();
                }
            }
        }
    }
    vector<string> generateParenthesis(int n)
    {
        vector<string> combinations;
        string comb;
        int no_openings = n, no_closings = n;
        dfs(combinations, comb, no_openings, no_closings);
        return combinations;
    }
};

// Method 2:- Using stack
class Solution
{
public:
    void gp(vector<string> combinations, int n)
    {
        stack<string> stk;
        int opening = n, closing = n;


    }
    vector<string> generateParenthesis(int n)
    {
    }
}
