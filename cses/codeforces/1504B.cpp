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
        ll n;
        cin>>n;
        vll a(n), b(n);
        inputVector(a,n);
        inputVector(b,n);
        bool result = true;
        ll iterations = log2(n)+1;
        while (iterations--)
        {
            ll count_0 = 0, count_1 = 0;
            for (int i = 0; i < n; i++)
            {
                a[i]==0 ? count_0++ : count_1++;
                if(a[i]!=b[i]){
                    if(count_0 == count_1){
                        //starting inverting the values of a
                        for (int j = 0; j <=i ; j++)
                        {
                            a[j] = (a[j]==0 ? 1 : 0);
                        }
                        continue;
                    }
                }
                else{
                    result = false;
                    break;
                }
            }
            
        }
        cout << (result==true? "YES" : "NO")<<endl;
    }
}
