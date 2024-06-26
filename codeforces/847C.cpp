#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    string field;
    cin >> field;

    vector<int> asterisks;
    vector<int> pacmen;

    for (int i = 0; i < n; i++)
    {
        if (field[i] == '*')
        {
            asterisks.push_back(i);
        }
        else if (field[i] == 'P')
        {
            pacmen.push_back(i);
        }
    }

    auto canEatAll = [&](int time)
    {
        int j = 0;
        for (int i = 0; i < pacmen.size() && j < asterisks.size(); i++)
        {
            int p = pacmen[i];
            if (p <= asterisks[j])
            {
                if (asterisks[j] - p > time)
                    return false;
                int limit = asterisks[j] + max(time - 2 * (asterisks[j] - p), (time - (asterisks[j] - p)) / 2);
                while (j < asterisks.size() && asterisks[j] <= limit)
                    j++;
            }
            else
            {
                if (p - asterisks[j] > time)
                    return false;
                int limit = p + max(time - 2 * (p - asterisks[j]), (time - (p - asterisks[j])) / 2);
                while (j < asterisks.size() && asterisks[j] <= limit)
                    j++;
            }
        }
        return j == asterisks.size();
    };

    int low = 0, high = 2 * n, ans = high;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (canEatAll(mid))
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << ans << '\n';
    return 0;
}
