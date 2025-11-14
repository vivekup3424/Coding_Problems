import { Service } from "node-windows";
import path from "path";
import args from "minimist";

export const service = new Service({
    name : "login_script_g",
    script: path.join(__dirname,"../dist/server.js"),
});

service.on("install",()=>{
    service.start();
    console.log("service started successfully...");
});

service.on("uninstall",()=>{
    service.stop();
    console.log("service uninstalled status-",!service.exists);
});

service.on("start",(d)=>{
    console.log("service started...",d);
});

service.on("alreadyinstalled",(d)=>console.log("already installed",d));
service.on("alreadyuninstalled",(d)=>console.log("already uninstalled",d));
service.on("error",(err)=>console.log("error occerd from service",err));

service.on("stop",()=>{

})

let arg = args(process.argv.slice());


if(arg?.install) service.install();
else if(arg?.uninstall) service.uninstall();