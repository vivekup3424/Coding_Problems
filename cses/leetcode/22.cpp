// 22. Genrate Parentesis

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    Solution *A = new Solution();
    vector<string> v = A->generateParenthesis(n);
    printVectorString(v);
}
void printVectorString(vector<string> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

class Solution
{
public:
    vector<string> generateParenthesis(int n)
    {
    }
};