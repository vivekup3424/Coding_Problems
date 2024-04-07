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
        //factorize with 2, and 3
        ll two = 0, three = 0;
        while(n %2 ==0){
            n = n/2;
            two++;
        }
        while(n%3==0){
            n = n/3;
            three++;
        }
        if(n!=1){
            cout<<-1<<endl;
        }
        else if(two > three)cout<<-1<<endl;
        else{
            cout<< 2*three - two<<endl;
        }
    }
}
