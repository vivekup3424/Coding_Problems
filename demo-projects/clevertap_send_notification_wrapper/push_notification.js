require("dotenv").config();
const axios = require("axios");

const CLEVERTAP_BASE_URL = "https://api.clevertap.com/1";

const headers = {
	"X-CleverTap-Account-Id": process.env.CLEVERTAP_ACCOUNT_ID || "449-R46-R57Z",
	"X-CleverTap-Passcode": process.env.CLEVERTAP_ACCOUNT_PASSCODE || "AAS-IAY-MPEL",
	"Content-Type": "application/json",
};

const pushPayload = {

	"to": {

		"objectId": [
			
			"-v8829d8dce13548df84dea2412686f8dd",
			"-vdd7ea2c414e843a1a4fb66b3b0e25343",
			
			"-2d1cc83f9f084a43b2eb3f0754b87a3a",

			"-24a6212992e04542b9ce361f31e7a923",

			"-v6bf1567abd1a48968f72718e9436e9e8",


			"-1281e7550d784915b77c9ddabe79cbf3",

			"-5707bb4001754239baf3c0699ccc872e"

		]

	},

	"content": {

		"title": "2 Doorbell Ringing - Dallas work HUB",

		"body": "You have a visitor at Main Door Unifi",

		"badge_icon": "notification",

		"platform_specific": {

			"android": {

				"large_icon": "https://heimdall.keus.in/Keus-199786d6-cf1f-47a7-87d9-af7f2a3ab9b0-kiotp.plugins.cameras.core/snapshot/6697bde601493403e4000460",

				"background_image": "https://heimdall.keus.in/Keus-199786d6-cf1f-47a7-87d9-af7f2a3ab9b0-kiotp.plugins.cameras.core/snapshot/6697bde601493403e4000460",

				"wzrk_cid": "slient_channel_id"

			},

			"ios": {

				"ct_mediaUrl": "https://heimdall.keus.in/Keus-199786d6-cf1f-47a7-87d9-af7f2a3ab9b0-kiotp.plugins.cameras.core/snapshot/6697bde601493403e4000460",

				"sound_file": "empty.wav",

				"mutable-content": "true"

			}

		},

		"params": "{\"notificationId\":\"47fpT4bX\",\"notificationSource\":\"CAMERA\",\"notificationBy\":\"+919999999999\",\"notificationUsername\":\"System\",\"notificationTime\":1770709913635,\"notificationType\":4,\"notificationStatus\":1,\"notificationPriority\":0,\"notificationData\":{\"applianceId\":\"Wj35n3NW\",\"applianceName\":\"Unifi VDP\",\"applianceRoom\":\"Home\",\"applianceSection\":\"Default\",\"applianceAccessPointId\":\"AP-tJVOTEzK\",\"detectionData\":{\"applianceId\":\"Wj35n3NW\",\"detectionType\":4,\"eventStartTime\":1770709909529,\"eventEndTime\":1770709917529,\"eventId\":\"698ae3990211ff03e44d1041\",\"eventThumbnailId\":\"https://heimdall.keus.in/Keus-199786d6-cf1f-47a7-87d9-af7f2a3ab9b0-kiotp.plugins.cameras.core/snapshot/6697bde601493403e4000460\"},\"notificationMessage\":\"Someone rang the doorbell\",\"silentDoorBell\":true},\"_id\":\"47fpT4bX\",\"gatewayId\":\"Keus-199786d6-cf1f-47a7-87d9-af7f2a3ab9b0\"}"

	},

	"ttl": {

		"ttl_type": "relative",

		"value": 604800

	}
};

async function sendPushNotification(payload = pushPayload) {
	try {
		const res = await axios.post(
			"https://api.clevertap.com/1/send/push.json",
			payload,
			{ headers }
		);
		console.log("Push notification sent successfully:", res.data);
		return res.data;
	} catch (err) {
		console.error("Error sending push notification:", err.response?.data || err.message);
		throw err;
	}
}

// Run directly
sendPushNotification();

module.exports = { sendPushNotification };
