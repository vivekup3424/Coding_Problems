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
        ll n;
        cin>>n;
        vll a(n);
        inputVector(a,n);
        int left = 0;
        bool result = true;
        while(left + 2 < n){
            if(a[left]==0){
                left++;
            }
            else{
                //check if there are three non- zero elements
                // including left
                if(a[left]>0 and a[left+1]>0 and a[left+2]>0){
                    //conduct operation
                    //if subtracting left by x, 
                    //subtract left+1 by 2x,....
                    ll x = a[left];
                    a[left]-=x;
                    a[left+1]-= 2*x;
                    a[left+2] -= x;
                }
                else{
                    result = false;
                    break;
                }
            }
        }   
        for(int i: a){
            if(i!=0){
                result=false;
                break;
            }
        }
        cout<<(result?"YES":"NO")<<endl;
    }
}
