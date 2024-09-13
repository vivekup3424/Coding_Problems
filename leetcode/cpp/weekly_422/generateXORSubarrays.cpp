#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

class Solution{
public:
    void generateXOR(vector<int> v){
        int n = v.size();
        for(int i = 0; i < n; i++){
            int num = 0;
            for(int j = i; j<n; j++){
                num = num ^ v[j];
                printf("i = %d, j = %d, ans = %d\n", i, j, num);
            }
        }
        cout<<"Ended\n";
    }
};
int main (int argc, char *argv[]) {
    auto A = new Solution();
    A->generateXOR({1,0,2,3,0,5});
    return 0;
}
