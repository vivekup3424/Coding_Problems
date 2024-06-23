#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int minOperationsToMakePalindrome(vector<int> &a, int k)
{
    int n = a.size();
    sort(a.begin(), a.end());
    map<int, int> freqHash;
    for (int i = 0; i < n; i++)
    {
        freqHash[a[i]]++;
        freqHash[a[i]] = freqHash[a[i]] / 2;
    }
    vector<int> leftOutElements;
    for (auto it : freqHash)
    {
        if (it.second == 1)
        {
            leftOutElements.push_back(it.first);
        }
    }
    // use dp to select pairs such that the diff maximum difference between pair is minimized
    // or maybe I should use something I like 2-sum
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    while (t--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
        }

        int result = minOperationsToMakePalindrome(a, k);
        cout << result << "\n";
    }

    return 0;
}
