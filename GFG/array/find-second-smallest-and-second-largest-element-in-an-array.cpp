#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    int secondLargestAndSmallestElement(vector<int> v){
        int maxi = v[0];
        int mini = v[0];
        for(auto n : v){
            if(n > maxi){
                maxi = n;
            }
            if(n < mini){
                mini = n;
            }
        }
        int secondMaxi = INT_MIN, secondMini = INT_MAX;
        for(auto n : v){
            if(n != maxi and n > secondMaxi){
                secondMaxi = n;
            }
        }
        return secondMaxi == INT_MIN ? -1 : secondMaxi;
    }
};
int main(){
    int T;
    cout<<"Enter the number of testcases\n";
    cin>>T;
    while(T--){
        int n;
        cout<<"Enter length of the array:- ";
        cin>>n;
        vector<int> v(n);
        cout<<"Enter the elements seperated by whitespace or newlines--\n";
        for(int i = 0; i < n; i++){
            int t;
            cin>>t;
            v[i] = t;
        }
        cout<<"Second Largest Number = "<<Solution().secondLargestElement(v)<<endl;
    }
}
