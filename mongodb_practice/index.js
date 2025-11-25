import express from "express";
const app = express()

app.get("/health", (req,res)=>{
    res.send("Local Shield is healthy");
})
app.get('/migrationStatus', (req,res)=>{
    const siteId = req.query.siteId;
    res.send({ siteId: siteId, state: "migrate"});
})

app.listen(7878, ()=>{
    console.log("Local Shield server running on port 7878");
})