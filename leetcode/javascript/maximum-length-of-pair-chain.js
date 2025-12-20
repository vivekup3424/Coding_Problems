var findLongestChain = function (pairs) {
    pairs.sort((a, b) => a[1] - b[1]);
    let current = Number.MIN_SAFE_INTEGER, answer = 0
    for(const [start,end] of pairs){
        if(start > current){
            answer+=1;
            current = end
        }
    }
    return answer
}