#include <iostream>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long x, y, k;
        cin >> x >> y >> k;

        while (k > 0)
        {
            long long next_divisible = ((x / y) + 1) * y;
            long long increment_steps = next_divisible - x;

            if (increment_steps <= k)
            {
                x = next_divisible;
                k -= increment_steps;
                cout << "X = " << x << ", K = " << k << endl;
                while (x % y == 0)
                {
                    x /= y;
                }
            }
            else
            {
                cout << "X = " << x << ", K = " << k << endl;
                x += k;
                k = 0;
            }
        }

        cout << x << endl;
    }
    return 0;
}
