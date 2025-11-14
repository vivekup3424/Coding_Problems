import puppeteer from "puppeteer";
import { checkSignedOutStatus, getCreds, logger, readStats, updateSignedOutStatus } from './constants';
import isReachable from "is-reachable";



export async function attendence(userName:string,password:string,signIn:boolean, retries: number = 3){

  if(retries == 0){
    return
  }

  const browser = await puppeteer.launch({ headless: true,executablePath:`C:/Program Files/Google/Chrome/Application/chrome.exe` });
  try{
    logger.info(""+signIn+checkSignedOutStatus(userName));

    const userAgent = 'Mozilla/5.0 (X11; Linux x86_64)' +
    'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.39 Safari/537.36';
    // Open a new page/tab
    const page = await browser.newPage();
    await page.setUserAgent(userAgent);

    // Navigate to a specific website
    try{
      await page.goto('https://keusautomation.greythr.com/'); // Replace with your desired website URL
    }
    catch(err){
      logger.info("failed to got url"+err);
    }
    await page.waitForSelector('#username')
    // Optional: Take a screenshot of the page
    await page.type("#username",userName);
    await page.type("#password",password)
    let button = await page.$x(`//button[contains(text(), 'Login')]`);
    //@ts-ignore
    let btn:HTMLButtonElement = button[0];
    await btn.click()
    await page.waitForNavigation({
      waitUntil: ['networkidle0','domcontentloaded','load'],
    });
    let button_sign = await page.evaluateHandle(():Promise<HTMLButtonElement>=>{
      // @ts-ignore
      return  document.querySelector(`body > app > ng-component > div > div > div.container-fluid.app-container.px-0 > div > ghr-home > div.page.page-home.ng-star-inserted > div > gt-home-dashboard > div > div:nth-child(2) > gt-component-loader > gt-attendance-info > div > div > div.btn-container.mt-3x.flex.flex-row-reverse.justify-between.ng-star-inserted > gt-button:nth-child(1)`).shadowRoot.querySelector("button")
    });

    // await button_sign.click();
    let text = `${await (await button_sign?.getProperty('textContent'))?.jsonValue()}`
    if(text == "Sign Out"){
        if(!signIn){
          await button_sign.click();  //sign out
          updateSignedOutStatus(userName,true);
          logger.info("signed out "+userName+","+checkSignedOutStatus(userName))
          console.log("signed out "+userName,",",checkSignedOutStatus(userName))
       }
       else{
        logger.info("already signed in "+userName+","+checkSignedOutStatus(userName));
        console.log("already signed in "+userName,","+checkSignedOutStatus(userName));
        updateSignedOutStatus(userName,false);
       }
    }
    else{
      if(signIn){
        await button_sign.click();  //sign in
        logger.info("signed in "+userName+","+checkSignedOutStatus(userName))
        console.log("signed in "+userName+","+checkSignedOutStatus(userName))
        updateSignedOutStatus(userName,false)
      }
      else{
        logger.info("already signed out "+userName+","+checkSignedOutStatus(userName));
        console.log("already signed out "+userName+","+checkSignedOutStatus(userName));
        // checkSignOut = true;
        updateSignedOutStatus(userName,true);
      }
    }

  }catch(err){
    console.log("failed to mark attendence",err)
    logger.warning("failed to mark attendence"+err)
    await browser.close();
    attendence(userName,password,signIn, retries - 1)
  }
  await browser.close();
}

export async function checkAttendence(date:Date,first?:boolean,id?:string){
    let hour = date.getHours();
    let creds = getCreds();
    await readStats();
    logger.info("from cron"+JSON.stringify(creds)+hour+date);
    console.log("from cron"+JSON.stringify(creds)+hour+date)
    
    try{

      if(!await isReachable("www.google.com",{timeout:10000})) {
        logger.info("laptop is offline can't proceed to login");
        console.log("laptop is offline can't proceed to login");
        return;
    }}
    catch(err){
      logger.info("failed to check attendence"+err);
      console.log("failed to check attendence",err);
      return;
    }

      for(const cred of creds){
        if(id && id != cred.userName) continue;
        
        logger.info("signed out status - > "+checkSignedOutStatus(cred.userName)+cred.In+","+cred.Out+"cur hr-"+hour);
        console.log("signed out status - > "+checkSignedOutStatus(cred.userName)+cred.In+","+cred.Out+"cur hr-"+hour)
        // if(hour>= (cred?.Out || 20)){
        if(hour>= (21)){
          try{
            if(!checkSignedOutStatus(cred?.userName) || first)
            await attendence(cred.userName,cred.password,false);
          }catch(err){
            logger.info("failed to check attendence for "+cred.userName+err);
            console.log("failed to check attendence",cred.userName,err);
          }
        // }else if(hour>= (cred.In || 9)){
        }else if(hour>= (9)){
          try{
            let day = date.getDay();
            if(checkSignedOutStatus(cred?.userName) || first)
            await attendence(cred.userName,cred.password,first? (day==0 || day == 6)? false:true:true);
          }
          catch(err){
            logger.info("failed to check attendence for "+cred.userName+err);
            console.log("failed to check attendence",cred.userName,err);
          }
        }
      }
    
}