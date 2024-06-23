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
int main1(){
    ll t;
    cin>>t;
    while(t--){
        ll n,k;
        cin>>n>>k;
        deque<ll> dq;
        for(int i = 0; i < n; i++){
            ll temp;
            cin>>temp;
            dq.push_back(temp);
        }
        bool first = true;
        while(k-- and dq.size()>0){
            if(first==true){
                dq.front() = dq.front() -1;
                first = false;
                if(dq.front()==0)dq.pop_front();
            }
            else if(first==false){
                dq.back() = dq.back() -1;
                first = true;
                if(dq.back()==0)dq.pop_back();
            }
        }
        cout<<n - dq.size()<<endl;
    }
}
int main(){
    ll t;
    cin>>t;
    while(t--){
        ll n,k;
        cin>>n>>k;
        deque<ll> dq;
        ll sum = 0;
        for(int i = 0; i < n; i++){
            ll temp;
            cin>>temp;
            sum += temp;
            dq.push_back(temp);
        }
        if(sum <=k){
            dq.resize(0);
        }
        bool first = true;
        while(k>0 and dq.size()>0){
            int minValue = min(dq.front(),dq.back());
            if(2*minValue > k){
                dq.front() -= (k+1)/2;
                dq.back() -= (k-1)/2;
                k=0;
            }
            else{
                k-= 2*minValue;
                dq.front() -= minValue;
                dq.back() -= minValue;
            }
            if(dq.front()==0)dq.pop_front();
            if(dq.size()>0 and dq.back()==0)dq.pop_back();
        }
        cout<<n - dq.size()<<endl;
    }
}