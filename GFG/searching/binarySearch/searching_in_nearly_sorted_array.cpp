// When your clueless about how to solve, then think about the parts of
// questions which you can solve from what you have learned

#include <bits/stdc++.h>
using namespace std;

// returns the index of k from nearly sorted array using binary search
int nearly_Binary_Search(vector<int> v, int low, int high, int k)
{
    int result = -1;
    int mid = low + (high - low) / 2;
    while (low < high)
    {
        if (k == v[mid])
            return mid;
        else if ((mid - 1) >= low and k == v[mid - 1])
            return mid - 1;
        else if ((mid + 1) <= high and k == v[mid + 1])
            return mid + 1;
        else if (k < v[mid - 1] and (mid - 2) >= low)
            high = mid - 2;
        else if (k > v[mid - 1] and (mid + 2) <= high)
            low = mid + 2;
    }
    return -1;
}

int main()
{
    int N = 5, K = 4;
    // cin >> N>>K;
    vector<int> V = {3, 2, 10, 4, 40};
    // for (int i = 0; i < N; i++)
    //{
    //     cin >> V[i];
    // }
    int result = nearly_Binary_Search(V, 0, V.size() - 1, K);
    cout << result << "\n";
    return 0;
}