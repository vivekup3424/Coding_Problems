#include <bits/stdc++.h>
using namespace std;
template <typename T>
void printMatrix(const vector<vector<T>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size(), cols = matrix[0].size();
        vector<vector<int>> consecutive_ones(rows, vector<int>(cols,0));
        for(int j = 0; j < cols; j++){
            for(int i = rows-1; i >=0; i--){
                char element = matrix[i][j];
                if(i==rows-1){
                    if(element=='0')consecutive_ones[i][j] = 0;
                    else if(element=='1')consecutive_ones[i][j] = 1; 
                }
                else if(element=='1'){
                    consecutive_ones[i][j] = consecutive_ones[i+1][j]+1;
                }
                else{
                    consecutive_ones[i][j] = 0;
                }
            }
        }
        printMatrix(consecutive_ones);
        //now doing the largest area of rectangle calculation
        int current_area = 0, max_area = 0;
        for(int i = 0; i < rows; i++){
            stack<int> stk; //decreasing stack, bottom value max
            for(int j = 0; j < cols; j++){
                int rectangle_length = consecutive_ones[i][j];
                if(stk.empty()==false and stk.top()==0){
                    //erase the empty the stack
                    while(stk.empty()==false)stk.pop();
                }
                while(stk.empty()==false 
                and 
                stk.top()<rectangle_length){
                    stk.pop();
                }
                stk.push(rectangle_length);
                current_area = stk.size()*stk.top();
                max_area = max(max_area,current_area);
            }
        }
        return max_area;
    }
};

int main() {
    Solution sol;
    vector<std::vector<char>> matrix = {
        {'1', '0', '1', '1', '0', '1'},
        {'1', '1', '1', '1', '1', '1'},
        {'0', '1', '1', '0', '1', '1'},
        {'1', '1', '1', '0', '1', '0'},
        {'0', '1', '1', '1', '1', '1'},
        {'1', '1', '0', '1', '1', '1'}
    };
  cout << sol.maximalRectangle(matrix) << endl;

    return 0;
}