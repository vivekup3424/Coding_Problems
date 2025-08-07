require("dotenv").config();
const axios = require("axios");

const endpoint = "https://api.clevertap.com/1/send/push.json";
const payload = {
  to: {
    Identity: ["+919740303762"]
    // Identity: ["+919553014924"]
    // Identity: ["+918247781785"]
  },
  content: {
    title: "Hello!",
    body: "This is a push notification.",
    locale: "en",
    button: {},
  }
};
const headers = {
	"X-CleverTap-Account-Id": process.env.CLEVERTAP_ACCOUNT_ID,
	"X-CleverTap-Passcode": process.env.CLEVERTAP_ACCOUNT_PASSCODE,
	"Content-Type": "application/json",
};

axios.post(endpoint,payload, {headers})
  .then(res => console.log("CleverTap response:", res.data))
  .catch(err => console.error("Error:", err));