#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long n, a, b;
        cin >> n >> a >> b;
        if (b <= a)
        {
            cout << n * a << endl;
        }
        else
        {
            long long k = min(b - a + 1, n);
            cout << (b - k + 1) * n + k * (k - 1) / 2 << endl;
        }
    }
    return 0;
}
