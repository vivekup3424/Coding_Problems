/**
 *INPUT FORMAT (file milkorder.in):
The first line contains N, M (1≤M<N), and K (1≤K<N), indicating that Farmer John has N cows, M of his cows have arranged themselves into a social hierarchy, and K of his cows demand that they be milked in a specific position in the order. The next line contains M distinct integers mi (1≤mi≤N). The cows present on this line must be milked in the same order in which they appear in this line. The next K lines contain two integers ci (1≤ci≤N) and pi (1≤pi≤N), indicating that cow ci must be milked in position pi.
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char const *argv[])
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> hierarchy(m);
    for (int i = 0; i < m; i++)
    {
        cin >> hierarchy[i];
    }
    vector<pair<int, int>> order(k);
    for (int i = 0; i < k; i++)
    {
        cin >> order[i].first >> order[i].second;
    }
    vector<int> ans(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        ans[hierarchy[i]] = i + 1;
    }
    vector<int> pos(n + 1, 0);
    for (int i = 0; i < k; i++)
    {
        pos[order[i].first] = order[i].second;
    }
    vector<int> cows;
    for (int i = 1; i <= n; i++)
    {
        if (pos[i] != 0)
        {
            cows.push_back(i);
        }
    }
    int l = 0, r = n;
    while (l < r)
    {
        int mid = (l + r) / 2;
        vector<int> temp = ans;
        for (int i = 0; i < mid; i++)
        {
            temp[cows[i]] = -1;
        }
        vector<int> order;
        for (int i = 1; i <= n; i++)
        {
            if (temp[i] != -1)
            {
                order.push_back(temp[i]);
            }
        }
        for (int i = 0; i < mid; i++)
        {
            order.push_back(-1);
        }
        bool flag = true;
        for (int i = 0; i < k; i++)
        {
            if (order[pos[order[i].first] - 1] != order[i])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << l << endl;
    return 0;
}
