#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> v;
        for (int i = 1; i <= n; i++)
        {
            if (i == n)
            {
                v.push_back(i);
            }
            else
            {
                v.push_back(i);
                v.push_back(i);
            }
        }
        sort(v.begin(), v.end(), greater<int>());
        int count = 0;
        while (k > 0 and count < v.size())
        {
            k -= v[count];
            count++;
        }
        cout << count << endl;
    }
    return 0;
}
