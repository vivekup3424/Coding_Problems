#include <bits/stdc++.h>
using namespace std;

void rearrange(vector<int> &v){
  int j = 0;
  for(int i = 0; i < v.size(); i++){
    if(v[j]<0){
      swap(v[i],v[j]);
      j++;
    }
  }
}

int main (int argc, char *argv[]) {
    int n;
    cout<<"Enter the length of array:-\t";
    cin>>n;
    vector<int> v(n);
    cout<<"Enter the elements of the array:-\n";
    for (int i = 0; i < n; i++) {
        cin>>v[i];
    }
    rearrange(v);
    cout<<"Sorted elements are:-\n";
    for(auto i : v){
        cout<<i<<" ";
    }
    cout<<endl;
    return 0;
}

