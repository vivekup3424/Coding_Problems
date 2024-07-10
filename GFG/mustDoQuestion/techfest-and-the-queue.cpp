#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

set<int> generatePrimes(){
    vector<bool> sieve(100001, false);
    set<int> primes;
    for(int i = 2; i < sieve.size(); i++){
        if(sieve[i]==false){
            primes.insert(i);
            for(int j = i*i; j < sieve.size(); j+=i){
                sieve[j] = true;
            }
        }   
    }
    return primes;
}
map<int,int> generatePowerPrimes(int n){
    map<int,int> powerPrimes;
    set<int> primes = generatePrimes();
    for (auto p : primes)
    {
        if(n>0 && n%p == 0){
            while (n>0 && n%p == 0)
            {
                powerPrimes[p]++;
                n /= p;
            } 
        }else if(p > n){
            break;
        }
    } 
    return {};
}
class Solution{
public:
    int sumOfPowers(int a,int b){
        int count=  0;
        for(int i = a; i <= b; i++){
            map<int,int> powerPrimes = generatePowerPrimes(i);
            for(auto p : powerPrimes){
                count += p.second;
            }
        }
        return count;
    }
};

int main(){
    int a = 9, b = 12;
    Solution A;
    cout << A.sumOfPowers(a,b);
}