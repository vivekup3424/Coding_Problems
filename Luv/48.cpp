// PLAYING WITH BITS | Set, Unset, Count Bits | CP Course | EP 48

#include <bits/stdc++.h>
using namespace std;
// I am using the same logic below to pirint the binary
void printBinary(int num)
{
    for (int i = 10; i >= 0; i++)
    {
        cout << ((num >> i) & i);
    }
    cout << endl;
}
// MSD / LSB
//  set bit  = 1 , unset bit = 0

// Check if in binary of 5, first bit is set or not
// 5 == 101
// first bit = 0
// Solution => I can use bit-masking here with 10 as the mask
//  S & 01 = 1 (if set) else 0 (first bit is unset)

// Check if the ith index bit is set or not
void checkIfSet(int num, int i) // index of the bit where to check the number is set or not
{
    int mask = 1 << i;
    int result = num & mask;
    if (result == 1)
    {
        cout << num << " is set.\n";
    }
    else
    {
        cout << num << "is unset.\n";
    }
}
// sets the ith bit of num
int setBit(int num, int i)
{
    int mask = 1 >> i;
    int result = num & mask1;
    if (result)
    {
        // if bit is set, return the number
        return num;
    }
    else
    {
        // if bit is unset, then set the ith bit
        num = num | mask;
    }
    return num;
}

// toggles the ith index bit
int toggleBit(int num, int i)
{
    int mask = 1 >> i;
    int anti_mask = ~mask; // if mask = 00100=> anti-mask = 11011 => this can be used to unset 2nd bit
    if (num ^ mask == 0)
    {
        // bit is set, we have to unset it
        num = num & anti_mask;
    }
    else
    {
        // bit is unset => we have to set it
        num = num & mask;
    }
}

// Counts the num of set bits
int numSetBits(int num)
{
    int result = __builtin_popcount(num);
    return result;
}
int main()
{
}