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
        ll a,b,c;
        cin>>a>>b>>c;
        //get the gcd
        int ans_c = 1;
        while(log10(ans_c) + 1 < c){
            ans_c =  (10 * ans_c) + 1;
        }
        //now getting the b, by multiplying with 2's
        int ans_b = ans_c;
        while(log10(ans_b)+1 < b){
            ans_b = (2*ans_b);
        }
        //multiplying with 3's to get a
        int ans_a = ans_c;
        while(log10(ans_a)+1 < a){
            ans_a = (3*ans_a);
        }
        cout<<ans_a<<" "<<ans_b<<endl;
    }
}
