require("dotenv").config();
const fs = require("fs")
const axios = require("axios");

const value = fs.readFileSync("./new_users_payload.json", "utf-8")
const headers = {
	"X-CleverTap-Account-Id": process.env.CLEVERTAP_ACCOUNT_ID,
	"X-CleverTap-Passcode": process.env.CLEVERTAP_ACCOUNT_PASSCODE,
	"Content-Type": "application/json",
};

axios
	.post("https://eu1.api.clevertap.com/1/upload", value, { headers })
	.then((res) => {
		console.log("Success:", res.data);
	})
	.catch((err) => {
		console.error("Error:", err.response?.data || err.message);
	});

