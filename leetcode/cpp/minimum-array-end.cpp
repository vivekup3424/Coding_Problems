#include <bits/stdc++.h>
#include <bitset>
using namespace std;
class Solution{
public:
    long long minEnd(int n, int x){
        bitset<32> bits(x);
        //out x in binary form
        cout<<bits<<endl;
        long long sum = 0;
        for(int i = 31; i >= 0 and n >= 0; i--){
            if(bits[i]==0){
                n-=2;
            }
            sum += 1<<i;
        }
        return sum;
    }
};
int main (int argc, char *argv[]) {
    cout<<"Enter n and x:-\n";
    int n,x;
    cin>>n>>x;
    cout<<Solution().minEnd(n, x);
    return 0;
}
