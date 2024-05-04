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
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n,m;
        cin>>n>>m;
        vector<vector<char>> mat(n,vector<char>(m,'#'));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin>>mat[i][j];
            }            
        }
        bool result = true;
        //in order to color the matrix with the same color, that 
        //color should be able to reach both the last row and last 
        //column hence that way it can propagate fully
        set<char> colorsFirstRow, colorsLastRow,
        colorsFirstCol, colorsLastCol;
        for (int i = 0; i < m ; i++)
        {
            colorsFirstRow.insert(mat[0][i]);
            colorsLastRow.insert(mat[n-1][i]);
        }
        for (int i = 0; i < n ; i++)
        {
            colorsFirstCol.insert(mat[i][0]);
            colorsLastCol.insert(mat[i][m-1]);
        }
        if(colorsFirstRow.size()==1 and 
        colorsLastRow.size()==1 and 
        mat[0][0]!=mat[n-1][0]){
            result = false;
        }       
        else if(colorsFirstCol.size()==1 and
        colorsLastCol.size()==1 and
        mat[0][0]!=mat[0][m-1]){
            result = false;
        }
        cout<<(result?"YES":"NO")<<endl;
    }
}