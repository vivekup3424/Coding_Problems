// find largerst sum contiguous subarray
// using Kadane's algorithm
#include <bits/stdc++.h>
using namespace std;
int start = 0, last = 0;
int max_sum(vector<int> v, int length) // length = size of array
{
    int max_so_far = INT_MIN;
    int current_max = 0;
    int /*start = 0, end = 0,*/ counter = 0;
    while (counter < length)
    {
        current_max += v[counter];
        if (current_max > max_so_far)
        {
            max_so_far = current_max;
        }
        else if (current_max < 0)
        {
            current_max = 0;
            start = counter + 1;
        }
        last = counter;
        counter++;
    }
    return max_so_far;
}
int main()
{
    vector<int> a = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = a.size();

    // Function Call
    int maximum = max_sum(a, n);
    cout << "Maximum contiguous sum is " << maximum << endl;
    cout << "start = " << start << endl;
    cout << "endl = " << last << endl;
    return 0;
}