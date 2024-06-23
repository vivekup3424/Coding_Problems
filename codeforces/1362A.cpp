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
        //solving it using bfs
        ll a,b;
        cin>>a>>b;
        ll c = max(a,b);
        ll d = min(a,b);
        ll r1 = c/d;
        ll temp = r1;
        while(temp%2 == 0){
            temp >>= 1;
        }
        if(temp > 1 or c%d!=0)cout<<-1<<endl;
        else {
            int count = 0;
            while(r1>=8){
                r1 >>=3;
                count++;
            }
            while(r1>=4){
                r1 >>=2;
                count++;
            }
            while(r1>=2){
                r1 >>=1;
                count++;
            }
            cout<<count<<endl;
        }
    }
}
