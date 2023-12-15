class Solution {
public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        vector<int> answer;
        for (const auto& query : queries) {
            int centerX = query[0];
            int centerY = query[1];
            int radius = query[2];
            
            int count = 0;
            for (const auto& point : points) {
                int pointX = point[0];
                int pointY = point[1];
                
                // Calculate the distance between the point and the center of the circle
                int distance = (pointX - centerX) * (pointX - centerX) + (pointY - centerY) * (pointY - centerY);
                
                // Check if the point is inside or on the border of the circle
                if (distance <= radius * radius) {
                    count++;
                }
            }
            
            answer.push_back(count);
        }
        
        return answer;
    }
};
