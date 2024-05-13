/**
 * @param {number[]} energy
 * @param {number} k
 * @return {number}
 */
var maximumEnergy = function(energy, k) {
    let n = energy.length;
    let dp = new Array(n);
    for (let index = 0; index < array.length; index++) {
        const element = array[index];
        let before = 0;
        if(index-k>=0){
            before = dp[index-k];
        }
        dp[index] = max(element,before+element)
    }
    let max_value = 0;
    for (let index = n-1; index >=n-1-k; index--) {
       max_value = max(max_value, dp[index]); 
    }
    return max_value;
};