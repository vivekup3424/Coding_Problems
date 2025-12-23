/**
 * @param {number} millis
 * @return {promise}
 */
async function sleep(millis){
    return new Promise((resolve)=>{
        setTimeout(()=>{
            resolve("dick")
        }, millis)
    })
}