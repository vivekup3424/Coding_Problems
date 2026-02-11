require("dotenv").config();
const axios = require("axios");

const eventData = {
	d: [
		{
			type: "event",
			identity: ["+918247781785"],
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
	"X-CleverTap-Account-Id": "449-R46-R57Z",
	"X-CleverTap-Passcode": "AAS-IAY-MPEL",
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

