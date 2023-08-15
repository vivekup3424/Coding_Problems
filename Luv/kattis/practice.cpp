
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int X, Y, N;
    cin >> X >> Y >> N;
    for (auto i = 1; i < N; i++)
    {
        if (i % X == 0 and i % Y == 0)
            cout << "FizzBuzz\n";
        if (i % X == 0)
            cout << "Fizz\n";
        else if (i % Y == 0)
            cout << "Buzz\n";
        else
        {
            cout << i << "\n";
        }
    }
}