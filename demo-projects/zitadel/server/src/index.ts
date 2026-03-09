import { verifyToken } from './proxy';
import { addOtp } from './zitadel/add-otp';
import { createUser } from './zitadel/create-user';
import { deleteUser } from './zitadel/delete-user';
import { getUser } from './zitadel/get-user';
import { createPatToken } from './zitadel/pat-token/create';
import { deletePatToken } from './zitadel/pat-token/delete';
import { introspectPatToken } from './zitadel/pat-token/introspect';
import { listAllPatTokens } from './zitadel/pat-token/list';
import { createSession } from './zitadel/session/create-session';
import { deleteSession } from './zitadel/session/delete-session';
import { getSession } from './zitadel/session/get-session';
import { updateSession } from './zitadel/session/update-session';

const domain = "auth.keus.in"
// const token = "yHtX1w9Lpv5Fusl7iy6NClIk7dFjzOj-5hbfsQyJXlXg9B_qhf8C3fjX4iRYGsgTxYSRRO0"
const token = "BXvBxnM9_W6pr2oSRqa4e2hdddsPhjCY5nqar6kFcGR2YMjkRZCLMl7BKiKryTO6CwjiryM"
const userId = "89a1d4c50000000000000000"
const sessionId = "334799016405499910"
const sessionToken = "KT292Uien31wr6Q_WCr6ewmjUhqDvRpohp_FPeSKzfrpT92WWJN_Ukid0Vbvw8MEgXE6-Jf9DSUK5Q"
// getUser(domain, token, userId)
// createUser(domain,token)
// addOtp(domain,token, userId)
// deleteUser(domain, token, userId)

// const machineToken = "RnFmT5Rd-gLgUTT1nrwjfqddGfpaAnG6bELqfHASdO2VKp8ggL8rjCy1a8PC6YXaL5l8tRo"
// introspectPatToken(domain, machineToken)

// createSession(domain, token, userId)
deleteSession(domain, sessionToken, sessionId)
// updateSession(domain, token, sessionId, "817467")
getSession(domain, sessionToken, sessionId)

const machineUser = "331289819499986950"
// createPatToken(domain, token, machineUser)
// deletePatToken(domain, machineUser, token, "329815212758663174")
// verifyToken("eyJhbGciOiJSUzI1NiIsImtpZCI6IjMyNjY2NDQ4NDk4MDUyMzAxNCIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJodHRwczovL2F1dGgua2V1cy5pbiIsInN1YiI6IjA5NGZjMDFiMDAwMDAwMDAwMDAwMDAwMCIsImF1ZCI6WyIzMjUwMzM4MTk1MTIwNDU1NzQiLCIzMjcyMTMwNDE2MjYxODU3MzQiLCIzMjcyMzQ5NjM2MjU4MDM3ODIiLCIzMjUwMzM2OTEzMTcyNzI1ODIiXSwiZXhwIjoxNzUyNTkxMTc3LCJpYXQiOjE3NTI1NDc5NzcsIm5iZiI6MTc1MjU0Nzk3NywiY2xpZW50X2lkIjoiMzI3MjEzMDQxNjI2MTg1NzM0IiwianRpIjoiVjJfMzI4OTIwNjM4MTEyNjYxNTEwLWF0XzMyODkyMDYzODExMjcyNzA0NiJ9.dNurwZmtQWWTYbh4UeHplhus5jDtI0ygokMeoyUmG-AR1bZL4Mv5bEBXqeAVlWesLdegYjGqzDLRfBPvBk60fK3mrp5j6GiqADr2Y_JImwINrrUnPYav_TRvxEP7esZTGuuQ5GqNvwPxCPCoDShIxYm9pbGgHrr7RVXWJyp5gVhdvvKkGuZ7KsZyDZDemjjIesn4WpHo-sPUBw3sn5VErxh6nw05Cx7Af5ulmKgcYGMPDHPSHMI9TIBavfmuN_-94ym-i64uPQo8zkb5zXS2Lx0FUIHwgP4YMCbknTNYtRjtinGfiBFihspbZCC4JXrNa7AYm58f6cBa_cnm8p_LEA")
// listAllPatTokens(domain, token, machineUser).then((result) => {
//     console.log("PAT Tokens:", result.length);

// }).catch((error) => {
//     console.error("Error listing PAT tokens:", error);
// });

// for (let i = 0; i < 1000; i++) {
//     for (let j = 0; j < 100; j++) {
//         createPatToken(domain, token, machineUser)
//     }
//     // await new Promise(resolve => setTimeout(resolve, 2000)); // Wait for 1 second before next batch
// }