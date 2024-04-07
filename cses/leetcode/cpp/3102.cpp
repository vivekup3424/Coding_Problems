#include <bits/stdc++.h>
using namespace std;
pair<int,int> findMaxJump(vector<vector<int>>& points)
{
    int maxJump = INT_MIN;
    int idx = 0;
    int n = points.size();
    for (int i = 1; i < n; i++)
    {
        int jump = abs(points[i][0] - points[i-1][0]) + abs(points[i][1] - points[i-1][1]);
        if(jump > maxJump){
            idx = i;
            maxJump = jump;
        }
    }
    return {maxJump,idx};
}
class Solution1 {
public:
    int minimumDistance(vector<vector<int>>& points) {
    int n = points.size();
    pair<int,int> p = findMaxJump(points);
    int idx = p.second;
    //I think I need to remove that thing which has the most contribution in jump  
    //try to remove first the idx element, and then idx-1 element
    //in seperate iterations
    //1
    vector<vector<int>> points1;
    for (int i = 0; i < n; i++)
    {
        if(i!=idx){
            points1.push_back(points[i]);
        }
    }
    pair<int,int> p1 = findMaxJump(points1);
    int jump1 = p1.first;

    vector<vector<int>> points2;
    for (int i = 0; i < n; i++)
    {
        if(i!=idx-1){
            points2.push_back(points[i]);
        }
    }
    pair<int,int> p2 = findMaxJump(points1);
    int jump1 = p2.first;

    return min({p.first,p1.first,p2.first});
    }
};
//I need to improve upon the above solution I am getting WA at 
/**
 * Input
points =
[[3,2],[3,9],[7,10],[4,4],[8,10],[2,7]]
Use Testcase
Output
9
Expected
10
*/

int main() {
    Solution1 solution;
    vector<vector<int>> points = {{3, 10}, {5, 15}, {10, 2}, {4, 4}};
    int result = solution.minimumDistance(points);
    cout << "Index of the point with the maximum jump: " << result << endl;
    return 0;
}