import fs from "fs/promises";
import {EventLogger} from "node-windows"
import { checkAttendence } from "./attendance";

export interface Creds{
    userName: string;
    password: string;
    In?: number;
    Out?: number;
}

let checkSignedOut:Record<string,boolean> = {}

export const checkSignedOutStatus = (id:string):boolean=>{
    return checkSignedOut[id]? true:false;
}

export const updateSignedOutStatus = async (id:string,status:boolean)=>{
    checkSignedOut[id] = status
    try{
        await fs.writeFile(statusFilePath,JSON.stringify(checkSignedOut));
    }catch(err){
        console.log("failed to update status file",err);
        logger.info("failed to update status file"+err);
    }
}

export const logger = new EventLogger({source:"login-script"});

const credFilePath = __dirname+"/../creds.json";
const statusFilePath = __dirname+"/../status.json";


let creds :Creds[];


export function getCreds():Creds[]{
    return creds;
}

export async function readStats(){
    try{
        checkSignedOut = JSON.parse(await fs.readFile(statusFilePath,{encoding:'utf-8'}));
    }catch(err){
        await fs.writeFile(statusFilePath,JSON.stringify({}));
        await initializeJson();
        await checkAttendence(new Date(),true);
    }
}

export async function readCredentials():Promise<{creds:Creds[],stats:Record<string,boolean>}>{
    let credsJson = "";
    try{
        credsJson = await fs.readFile(credFilePath,{encoding:"utf-8"});
        creds = await JSON.parse(credsJson);
        let statusJson = await fs.readFile(statusFilePath,{encoding:'utf-8'});

        if(creds.length == 0) creds = [{"userName":"1188","password":"Saiteja143##","In":9,"Out":18},{"userName":"1223","password":"shafiullakeus123@","In":9,"Out":18},{"userName":"1093","password":"Agnivo_keus123@","In":9,"Out":18}]
        
        checkSignedOut = <Record<string,boolean>> JSON.parse(statusJson);
        // console.log("got signedout statuses from file",checkSignedOut);
        for(let i=0; i<creds.length; i++){
            if(!checkSignedOut[creds[i].userName]) checkSignedOut[creds[i].userName] = false;
        }
    }catch(e){
        console.log("failed to parse json",e)
        logger.info("failed to parse json"+e);
    }
    console.log("json from read",creds);
    logger.info("json from read"+creds);
    return {creds,stats:checkSignedOut};

}

export async function updateCredentials(nc:Creds[],statuses?:Record<string,boolean>){
    creds = nc;
    try{
        let data =JSON.stringify(nc);
         await fs.writeFile(credFilePath,data);
         if(statuses)
         await fs.writeFile(statusFilePath,JSON.stringify(statuses));
    }catch(err){
        await fs.writeFile(credFilePath,JSON.stringify([]));
         if(statuses)
         await fs.writeFile(statusFilePath,JSON.stringify({}));
        console.log("failed to updatefiles",err);
        logger.info("failed to update files"+err);
        // await initializeJson()
    }
}

export async function initializeJson(){
    let readRes = await readCredentials();
    await updateCredentials(readRes.creds,readRes.stats);
}
