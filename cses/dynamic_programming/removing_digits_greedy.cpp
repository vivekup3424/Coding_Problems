#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    int count = 0;
    while (n > 0)
    {
        int max_digit = 0;
        int temp = n;
        while (temp > 0)
        {
            max_digit = max(max_digit, temp % 10);
            temp /= 10;
        }
        n -= max_digit;
        count++;
    }
    cout << count << endl;
    return 0;
}
