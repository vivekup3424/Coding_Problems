#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        string a, b;
        cin >> a >> b;

        // Calculate minimum Hamming distance
        int minHamming = INT_MAX;
        for (int i = 0; i <= n - m; i++)
        {
            int count = 0;
            for (int j = 0; j < m; j++)
            {
                if (a[i + j] != b[j])
                {
                    count++;
                }
            }
            minHamming = min(minHamming, count);
        }
        cout << minHamming << endl;
    }
    return 0;
}
