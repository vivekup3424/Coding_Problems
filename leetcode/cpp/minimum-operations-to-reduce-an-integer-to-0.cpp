#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minOperations(int n) {
        int numOperations = 0, numOnes = 0;
        while (n) {
            if(n&1){
                numOnes++;
            }else{
                if(numOnes>0){
                    numOperations++;
                }
                if(numOnes>1){
                    numOnes = 1;
                }else{
                    numOnes = 0;
                }
            }
            n>>=1; //leftbitshift
        }
        if(numOnes > 1) {
            numOperations+=2;
        }else if(numOnes==1){
            numOperations++;
        }
        return numOperations;
    }
};
int main (int argc, char *argv[]) {
    cout<<"Enter the number of testcases:-\t";
    int t;
    cin>>t;
    while (t--) {
        cout<<"Enter the number:-\t";
        int num;
        cin>>num;
        cout<<"Number of operations:-\t"<<Solution().minOperations(num)<<endl;
    }
    return 0;
}
