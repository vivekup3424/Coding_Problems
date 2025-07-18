require("dotenv").config();
const axios = require("axios");
const fs = require("fs");
const headers = {
  "X-CleverTap-Account-Id": process.env.CLEVERTAP_ACCOUNT_ID,
  "X-CleverTap-Passcode": process.env.CLEVERTAP_ACCOUNT_PASSCODE,
  "Content-Type": "application/json",
};
let cursor = null;
while (cursor) {
  if (cursor) {
    axios
      .post(
        `https://eu1.api.clevertap.com/1/profiles.json?cursor=${cursor}`,
        {},
        { headers }
      )
      .then((res) => {
        console.log("Success:", res.data);
        fs.writeFileSync("response", JSON.stringify(res.data));
      })
      .catch((err) => {
        console.error("Error:", err.response?.data || err.message);
      });
  } else {
    axios
      .post(`https://eu1.api.clevertap.com/1/profiles.json`, {}, { headers })
      .then((res) => {
        console.log("Success:", res.data);
        fs.writeFileSync("response", JSON.stringify(res.data));
      })
      .catch((err) => {
        console.error("Error:", err.response?.data || err.message);
      });
  }
}
