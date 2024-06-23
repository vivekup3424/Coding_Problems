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
bool isPalindrome(string s){
    int n = s.size();
    int i = 0, j = n-1;
    while(i<=j){
        if(s[i++]!=s[j--])return false;
    }
    return true;
}
int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while(T--)
    {
        ll n;
        cin>>n;
        string s;
        cin>>s;
        while (n>0)
        {
            string temp = s;
            //cout<<"Temp = "<<temp<<endl;
            reverse(s.begin(),s.end());
            //cout<<"S = "<<s<<endl;
            if(temp<s or isPalindrome(temp)){
                s = temp;
                //cout<<"reached"<<endl;
                break;
            }
            else{
                //first reverse the string
                //then append value to it
                s = s + temp;
                n-=2;//since we are doing two operations
            }
        }
        cout<<s<<endl;
    }
}
