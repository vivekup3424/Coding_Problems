#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        // create a minHeap
        priority_queue<int, vector<int>, greater<int>> minHeap;
        int a, b, c;
        cin >> a >> b >> c;
        minHeap.push(a);
        minHeap.push(b);
        minHeap.push(c);
        for (int i = 0; i < 5; i++)
        {
            int t = minHeap.top();
            minHeap.pop();
            t += 1;
            minHeap.push(t);
        }
        int p = 1;
        while (!minHeap.empty())
        {
            p *= minHeap.top();
            minHeap.pop();
        }
        cout << p << endl;
    }

    return 0;
}
