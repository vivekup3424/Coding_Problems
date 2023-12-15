// Nesting In Vectors: C++ STL For Beginners |
//  Competitive Programming Course | EP 22

#include <bits/stdc++.h>
using namespace std;
int main()
{
    int N;
    cin >> N;
    vector<int> v[N];
    for (int i = 0; i < N; i++)
    {
        int n;
        for (int j = 0; j < n; j++)
        {
            int temp;
            cin >> temp;
            v[i].push_back(temp);
        }
    }
}