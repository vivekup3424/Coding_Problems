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
        ll n,m,k,d;
        cin>>n>>m>>k>>d;
        //n = rows, m = cols, k = bridges, d = distance
        vector<vector<int>>mat(n,vector(m,0));
        for(int i = 0; i < n; i++){
            inputVector(mat[i],m);
        }

        vector<int> costs(n);
        //for first row
        
        for(int r = 0; r < n; r++){
            vector dp(m,INT_MAX);
            for(int i = 0; i <m; i++){
                if(i==0)dp[i] = 0;
                else{
                    int minCostBridge = INT_MAX;
                    for(int diff = 1; diff<=d+1; diff++){
                        int previousBridge = i - diff;
                        if(previousBridge < 0)continue;
                        else{
                            minCostBridge = min(minCostBridge,dp[previousBridge]);
                        }
                    }
                    int currentCost;
                    if(i==m-1){
                        currentCost = 0;
                    }
                    else{
                        currentCost = mat[r][i] + 1;
                    }
                    dp[i] = minCostBridge + currentCost;
                }
            }
            costs[r] = dp[m-1];
        }
        //do a sliding window of k-size on the costs
        int current_window = 0;
        for(int i = 0; i <k; i++){
            current_window += costs[i];
        }
        int min_cost = INT_MAX;
        for(int i = k; i < n; i++){
            min_cost = min(min_cost,current_window);
            current_window = current_window + costs[i] - costs[i-k];
        }
        cout<<min_cost<<endl;
    }
}
