class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector<pair<int, int>> dist(points.size());
        for (int i = 0; i < points.size(); ++i) {
            dist[i] = {points[i][0] * points[i][0] + points[i][1] * points[i][1], i};
        }
        nth_element(dist.begin(), dist.begin() + k - 1, dist.end());
        vector<vector<int>> result(k);
        for (int i = 0; i < k; ++i) {
            result[i] = move(points[dist[i].second]);
        }
        return result;
    }
};