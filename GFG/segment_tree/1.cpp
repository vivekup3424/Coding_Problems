//building up an segment tree
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int a[N], seg[4*N];

void build(int idx, int low, int high){
    if(low==high){
        seg[idx] = a[low];
        return;
    }
    int mid = (low + high)/2;
    build(2 * idx +1, low, mid);
    build(2*idx+2, mid+1, high);

    seg[idx] = max(seg[2*idx+1], seg[2*idx+2]);
}
int query(int idx, int low, int high, int l, int r){
    //range = low - high
    if(low >= l and high <= r){
        //range completely lies inside (l,r)
        return seg[idx];
    }
    if(high <l || low > r)return INT_MIN;

    //else overlaps
    int mid = (low + high)/2;
    int left = query(2*idx+1, low, mid, l,r);
    int right = query(2*idx+2, mid+1, high,l,r);
    return max(left, right);
}
int main(){
    int n;
    cin>>n;
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    build(0, 0,n-1);
    int q;
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<query(0,0,n-1,l,r);
    }
}