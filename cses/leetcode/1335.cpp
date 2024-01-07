#include <bits/stdc++.h>
using namespace std;

void build(vector<int> a, vector<int> &seg,int idx, int low, int high){
    if(low==high){
        seg[idx] = a[low];
        return;
    }
    int mid = (low + high)/2;
    build(a,seg,2 * idx +1, low, mid);
    build(a,seg,2*idx+2, mid+1, high);

    seg[idx] = max(seg[2*idx+1], seg[2*idx+2]);
}
int query(vector<int> &seg,int idx, int low, int high, int l, int r){
    //range = low - high
    if(low >= l and high <= r){
        //range completely lies inside (l,r)
        return seg[idx];
    }
    if(high <l || low > r)return INT_MIN;

    //else overlaps
    int mid = (low + high)/2;
    int left = query(seg,2*idx+1, low, mid, l,r);
    int right = query(seg,2*idx+2, mid+1, high,l,r);
    return max(left, right);
}
class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        if(jobDifficulty.size()>d)return -1;
        //build up an segment tree out of this array
        int n = jobDifficulty.size();
        vector<int> segmentTree(4*n,0);
        build(jobDifficulty,segmentTree,0,0,n-1);

        int current_sum = 0, max_sum = 0;
        int start = 0;
        int end = n-1;
        int j = n-1;
        while(j > 0){
            int s1 = query(segmentTree,0,0,n-1,start,j-1);
            int s2 = query(segmentTree,0,0,n-1,j,end);
            current_sum = s1 + s2;
            max_sum = max(current_sum, max_sum);
        }
        return max_sum;
    }
};

int main(){
    return 0;
}