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
void dfs(vector<vector<long long>> &grid, 
        long long rows, long long cols,
        long long i, long long j, 
        vector<vector<bool>> &visited,
        long long current_gcd, long long &max_gcd)
        {
            if(i<0 or j < 0 or i >= rows or j >= cols or visited[i][j]){
                return;        
            }
            visited[i][j] = true;
            current_gcd = __gcd(current_gcd, grid[i][j]);
            if(i==rows-1 and j == cols-1){
                max_gcd = max(max_gcd,current_gcd);
                //cout<<"I habe kmk\n";
                return;
            }
            dfs(grid,rows,cols,i,j+1,visited,current_gcd,max_gcd);
            dfs(grid,rows,cols,i+1,j,visited,current_gcd,max_gcd);
            visited[i][j] = false;
        }
int main()
{

    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll rows,cols;
        cin>>rows>>cols;
        vvll mat(rows,vll(cols,0));
        for (int i = 0; i < rows; i++)
        {
            for (int  j = 0; j < cols; j++)
            {
                cin>>mat[i][j];
            }
        }
        //I am going to solve this using dp
        
    }
}