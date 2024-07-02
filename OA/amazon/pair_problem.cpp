#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 *

Question 1
How to Attempt?
Pair Problem
Revisit Later
Lucy has an integer array A of size N. All the elements in the array are distinct. She can perform the following operation any number of times:
• Choose two numbers i and j in such a way that the product of the LCM (i,j) and HCF (ij) is present in array A.
Your task is to help Lucy find and return an integer value, representing the maximum number of valid (i,j) pairs which satisfy the given condition.
Note:
• The Least Common Multiple (LCM) of two numbers is the smallest number which is a multiple of both.
• The highest Common Factor (HCF) is the greatest number which divides each of the two or more numbers.
The Pair of (X,Y) is different from the pair of (Y,X).
Input Specification:
input1: An integer value N.
input2: An integer array A.
 */

/*Since we know that a * b = HCF(a,b)*LCM(a,b)
hence we can use a hashset and check whether for some pair a,b
does a*b exists in the hashset or not
*/

int countPairs(vector<int> v)
{
    int n = v.size();
    int count = 0;
    set<int> st;
    for (auto i : v)
    {
        st.insert(i);
    }
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (st.count(i * j))
            {
                count++;
            }
        }
    }
    return count;
}