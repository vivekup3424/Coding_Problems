#include <bits/stdc++.h>
using namespace std;
struct Comparator {
    bool operator()(const int a, const int b) const {
        return a > b;
    }
};

void selectionSort(vector<int> &v){
    for(int i = 0; i < v.size(); i++){
        int minIdx = i;
        int minValue = v[i];
        for(int j = i; j < v.size(); j++){
            if(v[j] < minValue){
                minIdx = j;
                minValue = v[j];
            }
        }
        swap(v[i],v[minIdx]);
    }
}
int main(){
    vector<int> v = {15,90,45,67};
    selectionSort(v);
    for(auto it : v){
        cout<<it<<" ";
    }
    cout<<endl;
}
