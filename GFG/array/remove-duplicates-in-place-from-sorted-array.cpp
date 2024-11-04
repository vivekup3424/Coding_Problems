/**Given an integer array sorted in non-decreasing order, 
 * remove the duplicates in place such that each unique 
 * element appears only once. The relative order of the 
 * elements should be kept the same.*/
#include <bits/stdc++.h>
using namespace std;

vector<int> removeDuplicates(vector<int> v){
    //since v is in a sorted form
    int j = 0;
    for(int i = 0; i < v.size(); i++){
        if(v[j]!=v[i]){
            j++;
            v[j] = v[i];
        }
    }
    return v;
}
int main (int argc, char *argv[]) {
    int T;
    cout<<"Enter the number of testcases:-";
    cin>>T;
    while (T--) {
        cout<<"Enter the length of array:-";
        int n;
        cin>>n;
        vector<int> v(n);
        cout<<"Enter the elements of the characters separated by whitespace or newline\\\n";
        for (int i = 0;i < n; i++) {
            int temp;
            cin>>temp;
            v[i] = temp;
        }
        sort(v.begin(),v.end()); //since the array is already sorted
        auto ans = removeDuplicates(v);
        cout<<"New array after removing the elements are:-\n";
        for(auto it : ans){
            cout<<it<<", ";
        }
        cout<<endl;
    }
    return 0;
}
