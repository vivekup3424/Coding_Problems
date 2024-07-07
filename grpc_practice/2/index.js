const fs = require('fs')
const http = require('http')
const { stringify } = require('querystring')
const employees = []
employees.push({ name: 'John', salary: 50000, id: 1 })

const nick = { name: 'Nick', salary: 100000, id: 2 }
employees.push(nick)

employees.push({ name: 'Andrew', salary: 70000, id: 3 })
for (let index = 0; index < 1000000; index++) {
    employees.push({"name": "Employee " + index.toString(), "salary": Math.random()*10000, "id": Math.random()*10000  
})
}
console.log(employees.slice(0, 10))
fs.writeFileSync('employees.json', JSON.stringify(employees))