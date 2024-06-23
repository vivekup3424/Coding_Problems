#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
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
        vll a(n);
        vll b(n);
        vll c(n);
        inputVector(a,n);
        inputVector(b,n);
        inputVector(c,n);
        sort(a.begin(),a.end());
        sort(b.begin(),b.end());
        sort(c.begin(),c.end());
        vll A = {a[n-3],a[n-2],a[n-1]};
        vll B = {b[n-3],b[n-2],b[n-1]};
        vll C = {c[n-3],c[n-2],c[n-1]};
        ll sum = 0, maxSum = 0;
        for(int i = 0;i < 3; i++){
            set<int> st;
            st.insert(i);
            sum += a[i];
            for (int j = 0; j < 3; j++)
            {
                if(!st.count(j)){
                    st.insert(j);
                    sum += b[j];
                }
                for (int k = 0; k < 3; k++)
                {
                    if(!st.count(k)){
                        st.insert(k);
                        sum += c[k];
                        maxSum = max(maxSum,sum);
                    }

                }   
            }
        }
        cout<<maxSum<<endl;
    }
}
