#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    const vector<string> belowTen = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    const vector<string> belowTwenty = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    const vector<string> belowHundred = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    const int ten = 1e1, twenty = 2e1, hundred = 1e2, thousand = 1e3, million = 1e6, billion = 1e9;
    string convertToWords(int num)
    {
        if (num < ten)
        {
            return belowTen[num];
        }
        if (num < twenty)
        {
            return belowTwenty[num - ten];
        }
        if (num < hundred)
        {
            return belowHundred[num / ten] + " " + convertToWords(num % 10);
        }
        if (num < thousand)
        {
            return convertToWords(num / hundred) + " Hundred" + " " + convertToWords(num % 100);
        }
        if (num < million)
        {
            return convertToWords(num / thousand) + " Thousand" + " " + convertToWords(num % 1000);
        }
        if (num < billion)
        {
            return convertToWords(num / million) + " Million" + convertToWords(num %)
        }
    }
    string numberToWords(int num)
    {
        if (num == 0)
        {
            return "zero";
        }
        return convertToWords(num);
    }
};