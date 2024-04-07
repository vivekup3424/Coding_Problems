// Prime Factorization using Sieve O(log n) for multiple queries
//  https://www.geeksforgeeks.org/prime-factorization-using-sieve-olog-n-multiple-queries/


/**
 * Sieve of Eratosthenes
 * Given a number n, print all prime numbers smallers than or equal to n.
 * Time Complexity: O(N*log(log(N)))
 * Auxiliary Space: O(N)
*/

//Question = https://www.geeksforgeeks.org/problems/techfest-and-the-queue1044/1

#include <bits/stdc++.h>
using namespace std;
class Solution{
public:
	int sumOfPowers(int a, int b){
	    // Code here
	}
};

//function to generate the prime factors of a number n
vector<int> generatePrimeFactors(int n){
    vector<bool> sieve(n+1,false);
    vector<int> ans;
    int m = sqrt(n) + 1;
    for (int p = 2; p < m; p++)
    {
        if(sieve[p]==true){
            ans.push_back(p);
        }
        for (int i = p*p; i <= n; i+=p)
        {
            sieve[i] = false;
        }
    }
    return ans;
}

//based on this, there is a efficient method to find the smallest prime factor
//for every integer
const int M = 2e5+1;
vector<int> SPF(M);
bool SPFgenerated = false;
void generateSPF(){
    if(SPFgenerated==true){
        return;
    }
    else{
        for(int i = 0; i <M; i++){
            SPF[i] = i;
        }
    }
    //sieve of erasthones subroutine
    for(int p = 2; p < M; p++){
        if(SPF[p]==p){
            for(int i = p*p;i < M; i+=p){
                SPF[i] = p;
            }
        }        
    }
}

vector<vector<int>> smallestPrimeFactors(int a,int b){
    //given integers a, and b, 
    //generate all the primes of integers between a and b
    int n = b - a +1;
    vector<vector<int>> factors(n);
    generateSPF();
    for (int i = a; i <= b; i++)
    {   vector<int> temp;
        int p = i;
        while (SPF[p]!=p)
        {
            temp.push_back(SPF[p]);
            p /= SPF[i];
        }
        temp.push_back(SPF[p]);
        factors.push_back(temp);
    }
}
int main()
{
    vector<vector<int>> matrix = smallestPrimeFactors(24,27);
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[0].size(); j++){
            cout<<matrix[i][j]<<endl;
        }
        cout<<endl;
    }
}