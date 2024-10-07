#include <algorithm>
#include <bits/stdc++.h>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int seed = 1234;
    int n = 4;
    vector<int> seeds;
    seeds.push_back(seed);
    for (int i = 1; i < 20; i++)
    {
        seed = seeds.back();
        int temp = seed * seed;
        string a = to_string(temp);
        if (a.length() < 2 * n)
        {
            reverse(a.begin(), a.end());
            while (a.length() < 2 * n)
            {
                a.push_back('0');
            }
            reverse(a.begin(), a.end());
        }
        string nextSeed = a.substr(n / 2, n / 2);
        int nextValue = stoi(nextSeed);
        seeds.push_back(nextValue);
    }

    for (auto i : seeds)
    {
        cout << i << " ";
    }
    cout << endl;
}
