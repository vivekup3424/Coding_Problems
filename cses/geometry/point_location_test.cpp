#include <bits/stdc++.h>
#include <complex>
using namespace std;
typedef long double C;
typedef complex<C> P;
#define X real()
#define Y imag()

int main()
{
    int t;
    cin >> t;
    int x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    int cp = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    if (cp < 0)
        cout << "RIGHT" << endl;
    if (cp > 0)
        cout << "LEFT" << endl;
    if (cp == 0)
        cout << "TOUCH" << endl;
}
/*function conj negates the y coordinate of
a vector, and when the vectors (x1 , −y1 ) and (x2 , y2 )*/

/*The cross product ( p − s1 ) × ( p − s2 ) tells us the location of the point p. If the
cross product is positive, p is located on the left side, and if the cross product is
negative, p is located on the right side. Finally, if the cross product is zero, the points
s1 , s2 , and p are on the same line.*/