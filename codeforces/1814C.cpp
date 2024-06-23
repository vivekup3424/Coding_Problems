#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cout.tie(NULL);
}

// Template function to input elements to a vector
template <typename T>
void inputVector(vector<T> &v, int n)
{
    v.resize(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> v[i];
    }
}

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
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n,s1,s2;
        cin>>n>>s1>>s2;
        int temp = min(s1,s2);
        int temp2 = max(s1,s2);
        s1 = temp; //min(s1,s2)
        s2 = temp2; //max(s1,s2)
        vll r(n,0);
        inputVector(r,n);
        priority_queue<pair<int,int>, vector<pair<int,int>>> maxHeap;
        for (int i = 0; i < n; i++)
        {
            maxHeap.push({r[i],i});
        }
        cout<<0<<endl;
    }
}
