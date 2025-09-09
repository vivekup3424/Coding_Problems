#include <iostream>
using namespace std;

int gcd(int a, int b)
{
    while (b)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int a, b;
        cin >> a >> b;
        int lcm_value = lcm(a, b);
        cout << (lcm_value != a) + (lcm_value != b) << endl;
    }
    return 0;
}