// make a function print(n) to print n to 1

#include <bits/stdc++.h>
using namespace std;
void print(int n)
{
    cout << n << ", ";
    if (n == 1)
        return;
    print(n - 1);
}
void print2(int n) // prints 1 to n
{
    if (n == 1)
    {
        cout << n << ", ";
        return;
    }
    print2(n - 1);
    cout << n << ", ";
}
int main()
{
    int N;
    cin >> N;
    print(N);
    cout << "---------------------\n";
    print2(N);
    return 0;
}