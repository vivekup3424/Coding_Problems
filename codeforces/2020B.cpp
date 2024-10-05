#include <bits/stdc++.h>
using namespace std;

// Template function to output elements of a vector
template <typename T>
void outputVector(const vector<T> &v, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
}
int main()
{
    // let's try to simulate the problems for 20 bulbs
    vector<bool> bulbs(40, 0);
    for (int i = 1; i <= 40; i++)
    {
        outputVector(bulbs, 40);
        for (int j = i; j <= 40; j++)
        {
            if (j % i == 0)
            {
                int idx = j - 1;
                bulbs[idx] = !bulbs[idx];
            }
        }
    }
}