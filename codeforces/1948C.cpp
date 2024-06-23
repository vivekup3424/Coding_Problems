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

bool solve(vector<vector<char>> &grid,vector<vector<bool>> visited,
            ll n,ll i, ll j, ll dest_i, ll dest_j)
{
    if(i==dest_i and j==dest_j){
        return true;
    }
    else if(i < 0 or j < 0 or i>=2 or j>=n or visited[i][j]==true){
        return false;
    }
    else{
        visited[i][j] = true;
        bool result = false;
        //moving left wards
        {
            ll new_i = i+1,new_j = j;
            if(
               new_i>=0 and new_i<2 
                and new_j>=0 and new_j<n
                and grid[new_i][new_j]=='>'){
                new_j++;
            }
            else{
                new_j--;
            }
            result |= solve(grid,visited,n,new_i,new_j,dest_i,dest_j);
        }
        //moving downwards
        {
            ll new_i = i,new_j = j+1;
            if(new_i>=0 and new_i<2 
                and new_j>=0 and new_j<n
                and grid[new_i][new_j]=='>'){
                new_j++;
            }
            else{
                new_j--;
            }
            result |= solve(grid,visited,n,new_i,new_j,dest_i,dest_j);

        }
        return result;
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
        vector<vector<char>> grid(2, vector<char>(n,'#'));
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < n; j++)
            {
                char c;
                cin>>c;
                grid[i][j] = c;
            }
        }
        vector<vector<bool>> visited(2,vector<bool>(n,false));
        cout<<(solve(grid,visited,n,0,0,1,n-1)? "YES": "NO")<<endl; 
                
    }
}
