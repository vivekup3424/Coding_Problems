// Write a function that takes two parameters n and k and returns the value of Binomial Coefficient C(n, k).

// Optimal Substructure
//  C(n,k) = C(n-1,k-1)+C(n-1,k)
//  C(n,0) = C(n,n) = 1 (base case), C(0,n) = 0
#include <iostream>
using namespace std;
int bionomial_coefficient(int n, int k) // nCk
{
    // overlapping subproblems
    if (k == 0 or n == k)
        return 1;
    else if (n < k)
        return 0;
    else
    {
        return bionomial_coefficient(n - 1, k - 1) + bionomial_coefficient(n - 1, k);
    }
    // Time Complexity: O(n*max(k,n-k))
    // Auxiliary Space : O(n * max(k, n - k))
}
// T(n,k) = T(n-1,k-1)+T(n-1,k)

int bionomial_coeff(int a, int b)
{
}
