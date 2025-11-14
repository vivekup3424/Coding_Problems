import express from "express";
import { attendence, checkAttendence } from "./attendance";
import cron from "node-cron"
import { Creds, checkSignedOutStatus, getCreds, initializeJson, logger, readCredentials, updateCredentials, updateSignedOutStatus } from "./constants";

const app = express();
let cronStarted = false;

async function startCron(){
    if(!cronStarted) {
        try{
            logger.info("starting cron");
            console.log("starting cron");
            checkAttendence(new Date(),true);
            //@ts-ignore
            cron.schedule("0 * * * 1-5",checkAttendence);
            // cron.schedule("* * * * * 1-5",checkAttendence);
            cronStarted = true;
        }
        catch(err){
            logger.info("error in cron job"+err);
            console.log("error in cron job"+err);
        }
    }
}

app.get("/",(req,res)=>res.send("<div style='text-align:center;'> <h2 style='margin:auto;display:inline-block;'><br/><br/>To update your credentials goto -<br/><br/> <span contenteditable='true'> http://localhost:7889/user?id={userName or id}&pass={password}</span> <br/><br/> if you want to set sign in and sign out go to (use 0-23 hrs format) <br/><br/> <span contenteditable='true'>http://localhost:7889/user?id={userName or id}&pass={password}&in=9&out=19</span> <br/><br/> <h1>enter details without curly braces</h1> <br/><br/> open developer console in chrome and paste the password inside this and add to password field => encodeURIComponent('') </h2> </div>"));

app.get("/getUsers",async(req,res)=>{
    let creds = await readCredentials();
    res.send(creds);
})

app.get("/user",async (req,res)=>{

    let start = false;

    let params = req.query;
    console.log(params)
    if(!params?.id) res.write("id required \n");
    if(!params?.pass) res.write("password required");
    if(params?.id && params?.pass) start= true;
    // console.log("before set in out")
    // if(params?.in || params?.out){
    //     setInAndOut(parseInt(<string>params?.in),parseInt(<string>params?.out));
    // }
    // console.log("before set in out")

    if(start){
        let creds:Creds = {
            userName: <string>params?.id,
            password: <string>params?.pass
        }

        if(params?.in) creds.In = parseInt(<string>params.in);
        if(params?.out) creds.Out = parseInt(<string>params.out);
        logger.info("credes from update"+creds)
        console.log("credes from update"+creds)

        let oldCreds = getCreds();

        let replace = false;

        let newCreds = oldCreds.map(cred => {
            let has = cred.userName == creds.userName;
            if(has) replace = true;
            else updateSignedOutStatus(creds.userName,false);

            return has? creds:cred;
        });
        
        try{
            await updateCredentials(replace? newCreds:[...oldCreds,creds]);
            checkAttendence(new Date(),true,<string>params?.id);
            if(start){
                await startCron();
            }
            else{
                logger.info("cron job already started!");
                console.log("cron job already started!");
            }
        }
        catch(err){
            logger.info("failed to update and read credentials"+err);
            console.log("failed to update and read credentials"+err);
        }
        
        res.write("credentials updated successfully!");
    }

    res.send();
})

async function init(){
    try{
        await initializeJson();
    }
    catch(err){
        logger.info("failed to initialize json data"+err);
        console.log("failed to initialize json data"+err);
    }
    
    let creds = getCreds();

    if(creds?.length > 0) {
        await startCron();
    }else{
        logger.info("not starting cron,no users exists from init...");
        console.log("not starting cron,no users exists from init...");
    }
}

async function start(){
    await init();
    app.listen(7889,()=>{
        logger.info("listening on port"+7889)
        console.log("listening on port"+7889)
    });
}

start();