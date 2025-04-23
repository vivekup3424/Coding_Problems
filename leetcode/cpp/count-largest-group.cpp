#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main (int argc, char *argv[]) {
    long long n;
    cin>>n;
    map<int,int> freq;
    int maxfreq = 0;
    for(long long i = 0; i <=n; i++){
        long long sum = 0, temp = i;
        while(temp>0){
            sum+=(temp%10);
            temp/=10;
        }
        freq[sum]+=1;
        maxfreq = max(maxfreq,freq[sum]);
    }
    int count = 0;
    for(auto it: freq){
        if(it.second==maxfreq){
            count++;
        }
    }
    return count;
}
class Solution{
public:
    int countLargestGroup(int n){
        map<int,int>freq;
        auto maxfreq = 0;
        for(auto i = 1; i<= n; i++){
            auto sum=0,temp=i;
            while(temp>0){
                sum+=(temp%10);
                temp/=10;
            }
            freq[sum]+=1;
            maxfreq=max(maxfreq,freq[sum]);
        }
        auto count = 0;
        for(auto it:freq){
            if(it.second==maxfreq){
                count++;
            }
        }
        return count;
    }
};
