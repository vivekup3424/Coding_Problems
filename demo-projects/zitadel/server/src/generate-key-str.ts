import fs from "fs/promises"
async function generateKeyStr(path: string){
    const file = await fs.readFile(path, "utf-8");
    const json = JSON.parse(file);
    console.log("JSON:", json);
}

generateKeyStr("./keys/api.txt")