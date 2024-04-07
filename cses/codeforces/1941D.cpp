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
        ll n,m,x;
        cin>>n>>m>>x; //n = players
        //0 = + clock
        //1 = - anti
        set<ll> st;
        st.insert(x);
        while(m--){
            ll steps;
            char direction;
            cin>>steps>>direction;
            set<ll> newSet;
            for(auto it: st){
                if(direction=='?'){
                    ll p1 = (steps + it)%n;
                    ll p2 = it - steps;
                    if(p2<0){
                        p2 = n+p2;
                    }
                    if(p1 == 0){
                        newSet.insert(n);
                    }
                    else{
                        newSet.insert(p1);
                    }
                    if(p2 == 0){
                        newSet.insert(n);
                    }
                    else{
                        newSet.insert(p2);
                    }
                }
                else if(direction=='0'){
                    ll p1 = (steps + it)%n;
                    if(p1 == 0){
                        newSet.insert(n);
                    }
                    else{
                        newSet.insert(p1);
                    }
                }
                else{
                    ll p2 = it - steps;
                    if(p2<0){
                        p2 = n+p2;
                    }
                    if(p2 == 0){
                        newSet.insert(n);
                    }
                    else{
                        newSet.insert(p2);
                    }
                }
            }
            st.clear();
            st = newSet;
        }
        cout<<st.size()<<endl;
        for(auto i : st){
            cout<<i<<" ";
        }
        cout<<endl;
    }
}
