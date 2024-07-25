#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        ll m;
        cin >> n >> m;
        vector<int> petals(n);
        for (int i = 0; i < n; i++)
        {
            cin >> petals[i];
        }

        // Compressing the array
        map<int, int> petalCount;
        for (int i = 0; i < n; i++)
        {
            petalCount[petals[i]]++;
        }

        // Storing petals and their counts in a vector of pairs and sorting
        vector<pair<int, int>> sortedPetals(petalCount.begin(), petalCount.end());
        sort(sortedPetals.begin(), sortedPetals.end());

        ll maxPetals = 0;
        ll currentCost = 0;
        ll currentPetals = 0;
        int left = 0;

        // Sliding window approach
        for (int right = 0; right < sortedPetals.size(); right++)
        {
            int petal = sortedPetals[right].first;
            int count = sortedPetals[right].second;
            currentPetals += ll(petal) * count;

            // Ensure the petal difference constraint is met
            while (sortedPetals[right].first - sortedPetals[left].first > 1)
            {
                currentPetals -= ll(sortedPetals[left].first) * sortedPetals[left].second;
                left++;
            }

            // Ensure the budget constraint is met
            while (currentPetals > m)
            {
                // Apply binary search to get the optimal number of petals to remove
                int l = 1, r = sortedPetals[left].second;
                while (l <= r)
                {
                    int mid = (l + r) / 2;
                    ll newCost = currentPetals - ll(sortedPetals[left].first) * mid;
                    if (newCost <= m)
                    {
                        r = mid - 1;
                    }
                    else
                    {
                        l = mid + 1;
                    }
                }

                // Remove `l-1` flowers from the left
                int removeCount = l;
                currentCost -= ll(sortedPetals[left].first) * removeCount;
                currentPetals -= ll(sortedPetals[left].first) * removeCount;
                sortedPetals[left].second -= removeCount;
                if (sortedPetals[left].second == 0)
                {
                    left++;
                }
            }

            maxPetals = max(maxPetals, currentPetals);
        }

        cout << maxPetals << '\n';
    }

    return 0;
}
