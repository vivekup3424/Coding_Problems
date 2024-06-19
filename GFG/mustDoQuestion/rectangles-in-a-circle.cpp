#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int rectangles_in_a_circle(int r)
{
    int d = 2 * r;
    int dSquared = d * d;
    int count = 0;
    for (int i = 1; i < d; i++)
    {
        int a = i;
        int b = sqrt(dSquared - (a * a));
        // cout << "a = " << a << ", b= " << b << endl;
        count += b;
    }
    return count;
}
int main()
{
    int a;
    cin >> a;
    cout << rectangles_in_a_circle(a) << endl;
}