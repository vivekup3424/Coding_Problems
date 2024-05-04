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
void dfs(vvll &mat,vector<vector<bool>> &visited,
        ll rows, ll cols, 
        ll x, ll y, ll &sum){
           if(x<0 or y<0 or x>=rows or y>=cols or visited[x][y]==true or mat[x][y]==0){
            return;
           }
           else{
            visited[x][y] = true;
            sum += mat[x][y];
            dfs(mat,visited,rows,cols,x+1,y,sum);
            dfs(mat,visited,rows,cols,x,y+1,sum);
            dfs(mat,visited,rows,cols,x-1,y,sum);
            dfs(mat,visited,rows,cols,x,y-1,sum);
           }
          return ; 
        }
int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n,m;
        cin>>n>>m;
        vvll mat(n,vll(m,0));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
               cin>>mat[i][j]; 
            }
        }
        vector<vector<bool>> visited(n,vector<bool>(m,false));
        ll maxSum  = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                ll sum = 0;
                if(visited[i][j]==false and mat[i][j]>0){
                    dfs(mat,visited,n,m,i,j,sum);
                }
                maxSum  = max(sum,maxSum);
            }
            
        }
       cout<<maxSum<<endl; 
    }
}