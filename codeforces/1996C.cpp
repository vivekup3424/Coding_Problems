#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

vector<vector<int>> preprocess_frequency(const string &s, int n)
{
    vector<vector<int>> freq(n + 1, vector<int>(26, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 26; ++j)
        {
            freq[i + 1][j] = freq[i][j];
        }
        freq[i + 1][s[i] - 'a'] += 1;
    }
    return freq;
}

int min_operations(int l, int r, const vector<vector<int>> &freq_a, const vector<vector<int>> &freq_b)
{
    int res = 0;
    for (int i = 0; i < 26; ++i)
    {
        int count_a = freq_a[r + 1][i] - freq_a[l][i];
        int count_b = freq_b[r + 1][i] - freq_b[l][i];
        res += abs(count_a - count_b);
    }
    return res / 2;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int n, q;
        cin >> n >> q;
        string a, b;
        cin >> a >> b;

        auto freq_a = preprocess_frequency(a, n);
        auto freq_b = preprocess_frequency(b, n);

        while (q--)
        {
            int l, r;
            cin >> l >> r;
            --l; // Convert 1-based to 0-based index
            --r;
            cout << min_operations(l, r, freq_a, freq_b) << "\n";
        }
    }

    return 0;
}
