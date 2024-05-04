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
template <typename T>
void printMatrix(const vector<vector<T>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
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
        vvll v(n, vll(n,0));
        vvll permutations;
        for(int row = 0; row < n; row++){
            vll perm;
            perm.push_back(1); //operation 1
            perm.push_back(row+1);
            for(int i = 1; i <=n; i++){
                v[row][i-1] = i;
                perm.push_back(i);
            }
            permutations.push_back(perm);
        }
        //doing the col-wise operations
        for(int col = 0; col < n-1; col++){
            vll perm;
            perm.push_back(2); //column-wise operation 2
            perm.push_back(col+1);
            for(int i = 1; i <= n; i++){
                v[i-1][col] = i;
                perm.push_back(i);
            }
            permutations.push_back(perm);
        }

        //last operation
        vll perm;
        perm.push_back(1);
        perm.push_back(1);
        for(int i = 0 ; i < n; i++){
            perm.push_back(i+1);
            v[0][i] = i+1;
        }
        permutations.push_back(perm);

        ll sum = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                sum += v[i][j];
            }
        }
        //start the output
        cout<<sum<<" "<<2*n<<endl;
        printMatrix(permutations);
        printMatrix(v);
    }
}