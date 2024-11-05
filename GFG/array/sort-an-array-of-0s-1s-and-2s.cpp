#include <bits/stdc++.h>
#include <utility>
using namespace std;

void sortColors(vector<int> &v){
    int i = 0, j = 0, k = v.size()-1;
    while (j<=k) {
        if (v[j]==0) {
            swap(v[i],v[j]);
            i++;
            j++;
        }else if(v[j]==1){
            j++;
        }else{
            swap(v[j],v[k]);
            k--;
        }
    }
}
int main (int argc, char *argv[]) {
    cout<<"Enter the length of the array:-\t";
    int n;
    cin>>n;
    cout<<"Enter the elements in the array, seperated by whitespace\n";
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin>>v[i];
    }
    sortColors(v);
    cout<<"Sorted elements in the array are;-\n";
    for(auto i : v){
        cout<<i<<" ";
    }
    cout<<endl;
    return 0;
}
