#include <bits/stdc++.h>
using namespace std;

int orientation(int x1, int y1, int x2, int y2, int x3, int y3)
{
    int val = (x3 - x2) * (y2 - y1) - (x2 - x1) * (y3 - y2);
    if (val > 0)
        return 1; // clockwise
    else if (val < 0)
        return 2; // counter-clockwise
    return 0;
}

bool onSeg