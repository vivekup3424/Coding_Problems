#include <bits/stdc++.h>
#include <cmath>
#include <vector>
using namespace std;

const double pi = M_PI;

class Solution {
private:
    double x1,y1;
public:
    double angleFromMe(vector<int> &point){
        double x2 = point[0], y2 = point[1];
        double m;
        if(x2!=x1){
            m = (y2 - y1)/(x2-x1);
        }else{
            m = MAXFLOAT;
        }
        return m;
    }
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        vector<int> angles;
        for(int i = 0; i < points.size(); i++){
            double m = angleFromMe(points[i]);
        }
        return 100;
    }
};
