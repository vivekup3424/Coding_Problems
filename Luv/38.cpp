// Generate Parenthesis: Advanced Recursion and Backtracking
//| CP Course
//| EP 38

// Given n pairs of parenthesis, write a function to generate all
// combinations of well-formed parentheses

#include <bits/stdc++.h>
using namespace std;
vector<string> combinations;
void generate_parethesis(string &comb, int open, int close) // open/close = num of opening/closing parentheses to be added
{
    if (open == 0 and close == 0) // all the parentheses have been added
    {
        combinations.push_back(comb);
        return;
    }
    if (open > 0)
    {
        comb.push_back('(');
        generate_parethesis(comb, open - 1, close);
        comb.pop_back();
    }
    if (close > 0)
    {
        if (open < close)
        {
            comb.push_back(')');
            generate_parethesis(comb, open, close - 1);
            comb.pop_back();
        }
    }
}
int main()
{
    int n;
    cin >> n;
    string empty = "";
    generate_parethesis(empty, 0, n);
    for (auto string : combinations)
    {
        cout << string << endl;
    }
}
