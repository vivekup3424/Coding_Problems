#include <bits/stdc++.h>
using namespace std;

int findMaxDiff(vector<int> &arr)
{
    int n = arr.size();
    // monotonically increasing stack
    stack<int> stk_left;
    stack<int> stk_right; // monotically increasing stack
    vector<int> left(n);
    vector<int> right(n);
    stk_left.push(0);
    for (int i = 0; i < n; i++)
    {
        while (stk_left.size() > 0 and stk_left.top() > arr[i])
        {
            stk_left.pop();
        }
        left[i] = stk_left.top();
        stk_left.push(arr[i]);
    }
    stk_right.push(0);
    for (int i = n - 1; i >= 0; i--)
    {
        while (stk_right.size() > 0 and stk_right.top() > arr[i])
        {
            stk_right.pop();
        }
        right[i] = stk_right.top();
        stk_right.push(arr[i]);
    }
    vector<int> diff(n);
    for (int i = 0; i < n; i++)
    {
        diff[i] = abs(left[i] - right[i]);
    }
    return *max_element(diff.begin(), diff.end());
}
int main()
{
    vector<int> arr = {32, 57, 21, 22};
    cout << findMaxDiff(arr) << endl;
}