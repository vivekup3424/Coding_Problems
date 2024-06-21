//repeat the string str x times
function replicate(str,x) {
    var temp = ""
    for (let i = 0; i < x; i++) {
        temp.concat(str)
    }
    console.log(temp)
}
replicate("dick",10)