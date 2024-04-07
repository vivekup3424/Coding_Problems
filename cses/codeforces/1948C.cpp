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
bool solve(vector<vector<char>> &grid,ll n,ll i, ll j, ll dest_i, ll dest_j)
{
    if(i==dest_i and j==dest_j){
        return true;
    }
    //choose where to move
    if(i==0){
        //right
        if(j+1<n and grid[i][j+1]=='>'){
            j++;
        }
        //down
        //
    }
}
int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n;
        cin>>n;
        vector<vector<char>> grid(2);
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < n; j++)
            {
                char c;
                cin>>c;
                grid[i][j] = c;
            }
        }
                
    }
}
