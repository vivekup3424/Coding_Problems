#include <bits/stdc++.h>
using namespace std;

/*
 *For a number n, printout the greatest perfect square, smaller than or equal to n
 * */

int perfectSquare(int n)
{
    int l = 1, r = n;
    int value = l;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        int square = mid * mid;
        if (square > n)
        {
            r = mid - 1;
        }
        else if (square == n)
        {
            value = mid;
            break;
        }
        else
        {
            value = l;
            l = mid + 1;
        }
    }
    cout << value * value << endl;
    return l * l;
}
int main()
{
    cout << "Enter the value of n: " << endl;
    int n;
    cin >> n;
    perfectSquare(n);
    return 0;
}
