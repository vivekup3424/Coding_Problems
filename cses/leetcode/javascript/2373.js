/**
 * @param {number[][]} grid
 * @return {number[][]}
 */
const largestLocal = function(grid) {
    let rows = grid.length;
    let cols = grid[0].length;
    let origin_x = 1, origin_y = 1;
    let ans = [];
    let counter = 0;
    for (; origin_x <= rows - 2; origin_x++) {
        let temp = [];
        let i = 0;
        origin_y = 0; // Reset origin_y for each row
        for (; origin_y <= cols - 2; origin_y++) {
            let value = Math.max(
                grid[origin_x - 1][origin_y - 1],
                grid[origin_x - 1][origin_y],
                grid[origin_x - 1][origin_y + 1],
                grid[origin_x][origin_y - 1],
                grid[origin_x][origin_y],
                grid[origin_x][origin_y + 1],
                grid[origin_x + 1][origin_y - 1],
                grid[origin_x + 1][origin_y],
                grid[origin_x + 1][origin_y + 1]
            ); 
            temp[i] = value;
            i++;
        }
        ans.push(temp);
    }
    return ans;
};

var matrixArray = ()=>{
    const a = new Array(4);
    for (let i = 0; i < a.length; i++) {
       a[i] = new Array(4);
       for (let j = 0; j < a[i].length; j++) {
        a[i][j] = `[${i} ${j}]`;
       }
    }
}
matrixArray();