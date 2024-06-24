#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const int MOD = 1e9+7;

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
    ll T=1;
    while (T--)
    {
        freopen("mixmilk.in","r",stdin);
        freopen("mixmilk.out","w",stdout);
        vll capacities(3,0);
        vll size(3,0);
        for(int i = 0; i < 3; i++){
            ll c,s;
            cin>>c>>s;
            capacities[i] = c;
            size[i] = s;
        }
        //doing shufffling
        for(int i = 0; i < 100; i++){
            if(i%3==0){
                //move from first bucket to second bucket
                if(size[0] <=(capacities[1]-size[1])){
                    size[1] += size[0];
                    size[0] = 0;
                }
                else{
                    size[0] -= (capacities[1]-size[1]);
                    size[1] = capacities[1];
                }
            }
            if(i%3==1){
                //move from second bucket to third bucket
                if(size[1] <=(capacities[2]-size[2])){
                    size[2] += size[1];
                    size[1] = 0;
                }
                else{
                    size[1] -= (capacities[2]-size[2]);
                    size[2] = capacities[2];
                }
            }
            if(i%3==2){
                //move from third bucket to first bucket
                if(size[2] <=(capacities[0]-size[0])){
                    size[0] += size[2];
                    size[2] = 0;
                }
                else{
                    size[2] -= (capacities[0]-size[0]);
                    size[0] = capacities[0];
                }
            }
        }
        for (int i = 0; i < 3; i++)
        {
            cout<<size[i]<<endl;
        }
    }
}