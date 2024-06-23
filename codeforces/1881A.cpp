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

int main()
{
    fast_io();
    ll N;
    cin>>N;
    int temp = INT_MAX;
    for(int i = 0; i < N; i++){
        int t;
        cin>>t;
        temp = min(temp, abs(t));
    }
    cout<<temp<<endl;
}
