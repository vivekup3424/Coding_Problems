#include <bits/stdc++.h>
#include <complex>
using namespace std;
typedef long double C;
typedef complex<C> P;
#define X real()
#define Y imag()

int cross(P a, P b, P c) // does cross product of two vectors with a as common vertex
{
    P u = b - a;
    P v = c - a;
    return (conj(u) * v).Y;
}
bool comp(const P &a, const P &b)
{
    return (a.X == b.X) ? (a.Y < b.Y) : (a.X < b.X);
}
bool mid(P a, P b, P c)
{
    vector<P> v = {a, b, c};
    sort(v.begin(), v.end(), comp);
    return (v[1] == c);
}

int sgn(int x)
{
    return (x > 0) - (x < 0);
}

bool check(P a, P b, P c, P d)
{
    int cp1 = cross(a, b, c);
    int cp2 = cross(a, b, d);
    int cp3 = cross(c, d, a);
    int cp4 = cross(c, d, b);
    if (cp1 == 0 && mid(a, b, c))
        return 1;
    if (cp2 == 0 && mid(a, b, d))
        return 1;
    if (cp3 == 0 && mid(c, d, a))
        return 1;
    if (cp4 == 0 && mid(c, d, b))
        return 1;
    if (sgn(cp1) != sgn(cp2) && sgn(cp3) != sgn(cp4))
        return 1;
    return 0;
}
int main()
{
    int t;
    cin >> t;
    int x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
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