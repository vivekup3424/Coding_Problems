var parser = function(str:String){
    if(str == "null"){
        return null
    }
    if(str.at(0)=="{" && str.at(str.length-1)=="}"){
        newString = str.slice(1,-1);
        newString.split
    }
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