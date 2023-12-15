
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> exit(n), entry(n);
    // calculate the max value using prefix sum computation
    int sum = 0, maxSum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> exit[i] >> entry[i];
        sum += (entry[i] - exit[i]);
        maxSum = max(sum, maxSum);
    }
    cout << maxSum << endl;
}