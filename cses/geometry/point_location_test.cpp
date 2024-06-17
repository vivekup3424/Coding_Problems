#include <bits/stdc++.h>
using namespace std;

// BeginCodeSnip{Point Class}
struct Point
{
    int x, y;
    Point(int a = 0, int b = 0) : x(a), y(b) {}

    friend istream &operator>>(istream &in, Point &p)
    {
        int x, y;
        in >> p.x >> p.y;
        return in;
    }
};
// EndCodeSnip

long long collinear(Point p, Point p1, Point p2)
{
    return 1LL * (p.y - p1.y) * (p2.x - p1.x) -
           1LL * (p.x - p1.x) * (p2.y - p1.y);
}

int main()
{
    int test_num;
    cin >> test_num;
    for (int t = 0; t < test_num; t++)
    {
        Point p1, p2, p3;
        cin >> p1 >> p2 >> p3;

        if (collinear(p1, p2, p3) == 0)
        {
            cout << "TOUCH" << '\n';
        }
        else if (collinear(p1, p2, p3) < 0)
        {
            cout << "RIGHT" << '\n';
        }
        else
        {
            cout << "LEFT" << '\n';
        }
    }
}
/*function conj negates the y coordinate of
a vector, and when the vectors (x1 , −y1 ) and (x2 , y2 )*/

/*The cross product ( p − s1 ) × ( p − s2 ) tells us the location of the point p. If the
cross product is positive, p is located on the left side, and if the cross product is
negative, p is located on the right side. Finally, if the cross product is zero, the points
s1 , s2 , and p are on the same line.*/