// Let's suppose that we have an array sorted in descending order
// and we want to find index of an element e within this array.
// Binary search in every step picks the middle element (m) of
// the array and compares it to e. If these elements are equal,
// than it returns the index of m. If e is greater than m, than
// e must be located in the left subarray. On the contrary, if
// m greater than e, e must be located in the right subarray.
// At this moment binary search repeats the step on the respective subrarray.
//
// Because the algoritm splits in every step the array in half (and one half of the array is never processed) the input element must be located (or determined missing) in at most \\log_{2}{n} steps.
#include <bits/stdc++.h>
using namespace std;
int BS_reverse_array(vector<int> V, int value)
{
    int low = V.size() - 1;
    int high = 0;
    int mid; // prevents overflow
    bool result = false;
    while (low >= high)
    {
        mid = low + (high - low) / 2; // prevents overflow
        if (V[mid] == value)
        {
            result = true;
            return mid + 1; // returns position, not index
        }
        if (value > V[mid])
        {
            low = mid - 1;
        }
        else
        {
            high = mid + 1;
        }
    }
    if (!result)
        return -1;
}
int main()
{
    int N;
    cin >> N;
    vector<int> V(N);
    // for (int i = 0; i < N; i++)
    //{
    //     cin >> V[i];
    // }
    V = {7,
         6,
         5,
         4,
         3,
         2,
         1};
    int result = BS_reverse_array(V, 1);
    cout << result << "\n";
    return 0;
}