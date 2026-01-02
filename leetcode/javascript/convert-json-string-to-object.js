/**
 * @param {string} str 
 * @return {object}
 */
var parser = function(str){
}

const test = {
    "apple": 123,
    "orange": "something",
    "fruits": {
        "apple": 123,
        "orange":"something",
    },
    "list": ["apple","orange", 2]
}
const testInString = '{"apple":123,"orange":"something","fruits":{"apple":123,"orange":"something"},"list":["apple","orange",2]}'
console.log(JSON.stringify(test))

console.log("output of the parser")
parser(testInString)