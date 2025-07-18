require("dotenv").config();
const axios = require("axios");

const eventData = {
	d: [
		{
			type: "event",
			identity: "vivek.upadhyay@keus.in",
			evtName: "Security_Tab_Viewed",
			evtData: {
				"timestamp": "12:46",
				"screen_name": "some_screen",
				"tab": "12RET",
			},
		},
	],
};

const headers = {
	"X-CleverTap-Account-Id": process.env.CLEVERTAP_ACCOUNT_ID,
	"X-CleverTap-Passcode": process.env.CLEVERTAP_ACCOUNT_PASSCODE,
	"Content-Type": "application/json",
};

axios
	.post("https://api.clevertap.com/1/upload", eventData, { headers })
	.then((res) => {
		console.log("Success:", res.data);
	})
	.catch((err) => {
		console.error("Error:", err.response?.data || err.message);
	});

