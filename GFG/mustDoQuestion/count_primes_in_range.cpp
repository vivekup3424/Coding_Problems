#include <bits/stdc++.h>
using namespace std;
const int M = 20000;
//using sieve of erasthones and prefuxSum
vector<bool> sieve(M,false);
vector<int> primesCount(M,0);
bool generated = false;
class Solution{
    public:
    void generatePrimes(){
        if(generated)return;
        generated = true;
        for (int p  = 2; p < M; p++)
        {
            if(sieve[p]==false){
                primesCount[p] = primesCount[p-1]+1; //number of primes till p
                for(int i = p*p; i < M; i+= p){
                    sieve[i] = true; //non-prime
                }
            }
            else{
                primesCount[p] = primesCount[p-1];
            }
        }   
}
    int countPrimes(int L,int R){
        generatePrimes();
        return primesCount[R] - primesCount[L];
    }
};
int main()
{
    Solution A;
    cout<<A.countPrimes(5,10)<<endl;
}