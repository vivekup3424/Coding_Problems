#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<long long> vll;
void inputVector(vll &v){
    int n = v.size();
    for(int i = 0; i <n; i++){
        cin>>v[i];
    }
}
int main(){
    ll t;
    cin>>t;
    while(t--){
        ll n,c,d;
        cin>>n>>c>>d;
        vll v(n*n,0);
        inputVector(v);
        ll minValue = *min_element(v.begin(),v.end());
        map<ll,ll> freq;
        for(auto num : v){
            freq[num]++;
        }
        bool result = true;
        vector<vll> mat(n, vll(n,-1));
        for(int i = 0; i <n; i++){
            for(int j = 0; j < n; j++){
                int value = 0;
                if(i==0 and j ==0){
                    value = minValue;
                    mat[i][j] = value;
                    freq[minValue]--;
                }
                else if(j==0){
                    value = mat[i-1][j] + c;
                    mat[i][j] = value;
                    if(freq.find(value)==freq.end()){
                        result = false;
                        break;
                    }
                    freq[value]--;
                }
                else{
                    value = mat[i][j-1] + d;
                    mat[i][j] = value;
                    if(freq.find(value)==freq.end()){
                        result = false;
                        break;
                    }
                    freq[value]--;
                }
                if(freq[value]==0){
                    freq.erase(value);
                }
            }
        }
        cout<<(result ? "YES" : "NO")<<endl;
    }
}