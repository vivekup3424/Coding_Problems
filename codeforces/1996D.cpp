#include <iostream>
using namespace std;

long long countTriplets(int n, int x)
{
    long long count = 0;

    // Iterate over possible values of a
    for (int a = 1; a <= x; ++a)
    {
        // Iterate over possible values of b
        for (int b = 1; b <= x; ++b)
        {
            // Calculate the maximum possible value of c for given a and b
            int maxC = min(x - a - b, (n - a * b) / (a + b));
            if (maxC >= 1)
            {
                count += maxC;
            }
        }
    }

    return count;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n, x;
        cin >> n >> x;
        cout << countTriplets(n, x) << endl;
    }

    return 0;
}
