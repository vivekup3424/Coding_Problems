#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//@returns {slope,intercept}
pair<double,double> generateLine(vector<int> &p1,vector<int> &p2){
    double dx = p1[0] - p2[0];
    double dy = p1[1] - p2[1];
    if(dx == 0){
        return {INT_MAX,p1[0]};
    }
    double slope = dy/dx;
    double intercept = p1[1] - slope*p1[0];
    return {slope,intercept};        
}

class Solution1 {
//brute force
public:
    int maxPoints(vector<vector<int>>& points) {
        if(points.size() <= 2) return points.size();
       //map to store the possible lines 
       map<pair<double,double>,int> lines;
       int n = points.size();
       for(int i = 0; i < n; i++){
           for(int j = i+1; j < n; j++){
               auto line = generateLine(points[i],points[j]);
               lines[line] = 0;
           }
       }
       for(auto it : lines){
              auto l = it.first;
              for(int i = 0; i < n; i++){
                if(l.first == INT_MAX){
                     if(points[i][0] == l.second){
                          lines[l]++;
                     }
                }else{
                     if(points[i][1] == l.first*points[i][0] + l.second){
                          lines[l]++;
                     }
                }
              }
        }
        int maxi = 0;
        for(auto it : lines){
            maxi = max(maxi,it.second);
        }
        return maxi;
    }
};

class Solution2 {
    int maxPoints(vector<vector<int>> &points){
        int n = points.size();
        int maxi = 1; //since there would be atleast one point
        for(int i = 0; i < n; i++){
            auto point = points[i];
            map<double,int> pointCount;
            for(int j = i+1; j < n; j++){
                double dy = points[j][1] - point[1];
                double dx = points[j][0] - point[0];
                double slope = INT_MAX;
                if(dx != 0){
                    slope = dy/dx;
                }
                pointCount[slope]++;
                maxi = max(maxi,pointCount[slope]+1);
            } 
        }
        return maxi;
    }
};