#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const int MOD = 1e9 + 7;

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
    ll T = 1;
    while(T--)
    {
        freopen("speeding.in", "r", stdin);
        freopen("speeding.out", "w", stdout);
        ll N, M;
        cin >> N >> M;
        vector<pair<ll,ll>> road(N);
        vector<pair<ll,ll>> bessie(M);
        for (int i = 0; i < N; i++)
        {
            ll length,speed;
            cin>>length>>speed;
            road[i] = {length,speed};
        }
        for (int i = 0; i < M; i++)
        {
            ll length,speed;
            cin>>length>>speed;
            bessie[i] = {length,speed};
        }
        ll i = 0, j = 0, k = 0;
        ll score = 0;
        while(k<100){
            ll increase = min(road[i].first,bessie[j].first);
            if(bessie[j].second > road[i].second){
                ll speed_diff =(bessie[j].second - road[i].second); 
                score = max(score,speed_diff);
            }
            road[i].first -= increase;
            bessie[j].first-=increase;
            if (road[i].first==0){
                i++;
            }
            if (bessie[j].first==0){
                j++;
            }
            k += increase;
        }        
        cout<<score<<endl;
    }
}