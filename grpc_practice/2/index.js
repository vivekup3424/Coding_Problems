const http = require('http')
const employees = []
employees.push({ name: 'John', salary: 50000, id: 1 })

const nick = { name: 'Nick', salary: 100000, id: 2 }
employees.push(nick)

employees.push({ name: 'Andrew', salary: 70000, id: 3 })

employees.push("sknkvls ll akllk ")
console.log(employees)
console.log(JSON.stringify(employees))