#include <iostream>
#include <complex>
using namespace std;
typedef long long C;
typedef complex<C> P;
#define X real()
#define Y imag()
int main()
{
    P p = {4, 2};
    cout << p.X << " " << p.Y << "/n";
    P a = {4, 2};
    P b = {3, -1};
    P c = a + b;
    cout << c.X << " " << c.Y << "\n";
    cout << "Absolute = " << abs(b - a) << "\n";
}