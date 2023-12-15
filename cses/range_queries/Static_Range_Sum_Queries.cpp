/*Given an array of n integers, your task is to process q queries of the form:
what is the sum of values in range [a,b]?*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
void printVector(vector<lli> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}
int main()
{
    int n, q;
    cin >> n >> q;
    vector<lli> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    vector<lli> prefix(n);
    prefix[0] = 0;
    prefix[1] = v[0]; // prefix sum computation
    for (int i = 2; i <= n; i++)
    {
        prefix[i] = prefix[i - 1] + v[i - 1];
    }
    // v = {1,2,3,4,5,6,7,8,9,10}
    //  prefix = {0,1,3,6,10,15,21,28,36,45,55}
    //   printVector(v);
    //   printVector(prefix);
    while (q--)
    {
        int a, b;
        cin >> a >> b;
        cout << prefix[b] - prefix[a - 1] << endl;
    }
}
