#include <bits/stdc++.h>
using namespace std;

struct Point
{
    long long x;
    long long y;
};
int product(Point P1, Point P2, Point P)
{
    // float m1 = (P1.y - P2.y) / (P1.x - P2.x);
    // float m2 = (P1.y - P.y) / (P1.x - P.x);
    //  if m1==m2 => parallel coincident
    int ans = (P1.y - P2.y) * (P1.x - P.x) - (P1.x - P2.x) * (P1.y - P.y);
    return ans;
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        struct Point A, B, C, D;
        cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y;
        int p1 = product(A, B, C);
        int p2 = product(A, B, D);
        int p3 = product(C, D, A);
        int p4 = product(C, D, B);
        if (p1 == 0 || p2 == 0 || p3 == 0 || p4 == 0)
        {
            cout << "YES\n";
        }
        else if ((abs(p1 + p2) < abs(p1) + abs(p2)) and (abs(p3 + p4) < abs(p3) + abs(p4)))
        {
            cout << "YES\n";
        }
        cout << "NO\n";
    }
    return 0;
}
