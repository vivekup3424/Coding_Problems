/**
 * @param {string} s
 * @param {string} t
 * @return {number}
 */
var findPermutationDifference = function(s, t) {
    let mp = {}
    for (let index = 0; index < s.length; index++) {
        const element = s[index];
        mp[element] = index;
    }    
    let sum = 0;
    for (let index = 0; index < t.length; index++) {
        const element = t[index];
        let index2 = mp[element];
        sum += Math.abs(index-index2); 
    } 
    console.log(`Sum = ${sum}`)
    return sum
};