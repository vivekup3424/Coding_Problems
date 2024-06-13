#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void generatePowerSet1(string str, int n, string temp, vector<string> &ans, int idx)
{
    if (idx == n)
    {
        ans.push_back(temp);
        return;
    }
    generatePowerSet1(str, n, temp, ans, idx + 1);
    temp.push_back(str[idx]);
    generatePowerSet1(str, n, temp, ans, idx + 1);
    temp.pop_back();
}
vector<string> generatePowerSet2(string str, int n)
{
    vector<string> ans;
    int N = pow(2, n);
    for (int i = 0; i < N; i++)
    {
        string temp;
        for (int j = 0; j < n; j++)
        {
            if ((i & (1 << j)) == 1)
            {
                temp.push_back(str[j]);
            }
        }
        ans.push_back(temp);
    }
    return ans;
}
int main()
{
    string str = "abc";
    vector<string> ans;
    string temp = "";
    // generatePowerSet(str, str.size(), temp, ans, 0);
    ans = generatePowerSet2(str, str.size());
    for (string s : ans)
    {
        cout << s << endl;
    }
    return 0;
}