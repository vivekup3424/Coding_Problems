// Power of XOR Operator | CP Course | EP 50

#include <bits/stdc++.h>
using namespace std;

int main1()
{
    // swapping a & b using XOR
    int a = 4, b = 5;
    b = a ^ b;
    a = a ^ b; //=> a = a^a^b = b
    b = a ^ b; // b^a^b = a
    // hence a and b are swapped
}

///////////////////////////
// Given an array A of n integers. All integers are present in even count
//  except one, find that odd count integer
int main()
{
    int n;
    vector<int> v;
    while (n--)
    {
        int temp;
        cin >> temp;
        v.push_back(temp);
    }
    int result = 0;
    int i = 0;
    while (i < v.size())
    {
        result = result ^ v[i];
    }
    // Time complexity = O(n)
    // Space Complexity = O(1)
}