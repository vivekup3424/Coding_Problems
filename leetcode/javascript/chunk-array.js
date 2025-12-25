/**
 * @param {Array} arr
 * @param {Number} size
 * @return {Array}
 */
var chunk = function (arr, size) {
    if(!Number.isInteger(size) || size <= 0) return [];
    const answer = []
    let i = 0;
    while (i < arr.length){
        const temp = [];
        let j = 0;
        while(i+j<arr.length && j < size){
            temp.push(arr[i+j]);
            j++;
        }
        answer.push(temp);
        i = i+j;
    }
    return answer;
}