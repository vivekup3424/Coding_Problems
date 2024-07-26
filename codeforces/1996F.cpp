#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;

long long max_score_after_k_operations(int n, long long k, vector<long long> &a, vector<long long> &b)
{
    priority_queue<pair<long long, long long>> max_heap;

    for (int i = 0; i < n; ++i)
    {
        max_heap.push({a[i], b[i]});
    }

    long long score = 0;

    while (k > 0 && !max_heap.empty())
    {
        auto [current_value, decrement] = max_heap.top();
        max_heap.pop();
        score += current_value;
        k -= 1;
        long long new_value = current_value - decrement;
        if (new_value > 0)
        {
            max_heap.push({new_value, decrement});
        }
    }
    return score % MOD;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        int n;
        long long k;
        cin >> n >> k;

        vector<long long> a(n), b(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
        }
        for (int i = 0; i < n; ++i)
        {
            cin >> b[i];
        }

        cout << max_score_after_k_operations(n, k, a, b) << endl;
    }

    return 0;
}
