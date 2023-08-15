// 6 Amazing BIT Manipulation Ticks You must Know | CP Course | EP 49

#include <bits/stdc++.h>
#include "48.h"
using namespace std;

// Checks even/odd
void oddEven(int num)
{
    if (num & 1)
    {
        cout << "odd\n";
    }
    else
    {
        cout << "even\n";
    }
    // this method is faster than regular arithmetic
}
bool isPowerOfTwo(int num)
{
    int result = num & num - 1;
    if (result)
        return false;
    else
        return true;
}
int main()
{
    int n = 5;
    n >> 1; // divides the number by 2
    n >> 2; // divides the number by 2^2 = 4 ...
    n << 2; // multiplies the number by 4 ...

    /////////////////////////////////////////////////////////
    // Toggling Characters from Uppercase to Lowercase  and vice-versa
    for (char c = 'A'; c <= 'Z'; c++)
    {
        cout << c << "=>";
        printBinary(int(c));
    }
    char A = 'A';
    char a = A | (1 << 5); // toggling Uppercase to lowercase by setting the 5th bit
    // convert to uppercase by unsetting the 5th bit
    cout << char(a & (~(1 << 5))) << "\n";

    // also since char(1<<5) == ' '
    // I can also do this
    char C = 'C';
    char c = C | ' ';
    // C = char (c & '_') => this toggles the lowercase to uppercase

    //////////////////////////////////////////////////
    // Clear LSBs
    // Given a number, do an operation to unset all the LSBs till nth index
    int num, i;
    cin >> num >> i; // i is the index of leftmost LSB to be unset or cleared
    int result = num & (~(1 << (i + 1) - 1));

    ///////////////////////////////////////////////
    // Clear MSBs
}