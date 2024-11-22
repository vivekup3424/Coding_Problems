import os from "os";
import { createServer } from "node:http";
let interfaces = os.networkInterfaces();
console.log(interfaces);
//encoding object to map
let interfacesMap = new Map(Object.entries(interfaces));
let address = "";
interfacesMap.forEach((config, keyInterface) => {
  if (keyInterface != "lo" && keyInterface != undefined) {
    //not localhost
    address = config[0]["address"];
    console.log(`address of device = ${address}`);
  }
});
const port = 8000;
const server = createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader("Content-Type", "text/plain");
  res.end("Hello World");
});
server.listen(port, address, () => {
  console.log(`Server running at http://${address}:${port}/`);
});
