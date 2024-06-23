
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int k, n, w;
    // k,2k,3k...,k + (i-1)k = wk=>Sum = w/2*(k+wk) (sum of AP)
    cin >> k >> n >> w;
    int t = ((w / 2) * (k + w * k)) - n;
    cout << (t > 0 ? t : 0) << endl;
}