import * as readline from "node:readline/promises"
import { stdin, stdout } from "node:process"

const readWrite = readline.createInterface({
    input: stdin,
    output: stdout,
});
(async () => {
    const answer = await readWrite.question("What is the color of apple??")
    readWrite.write(`Oh so color of apple is ${answer}\n`)
})()
