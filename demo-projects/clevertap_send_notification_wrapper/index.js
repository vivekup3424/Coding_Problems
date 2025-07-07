const CleverTap = require('clevertap')
require("dotenv").config()

// console.log(process.env.CLEVERTAP_ACCOUNT_ID)
// console.log(process.env.CLEVERTAP_ACCOUNT_PASSCODE)
// console.log(process.env.CLEVERTAP_ACCOUNT_REGION)

const clevertap = CleverTap.init(
	process.env.CLEVERTAP_ACCOUNT_ID,
	process.env.CLEVERTAP_ACCOUNT_PASSCODE,
	process.env.CLEVERTAP_ACCOUNT_REGION)

var data = [
	{
		type: "event",
		identity: process.env.CLEVERTAP_ACCOUNT_ID,
		evtName: "Charged",
		evtData: {
			a: "789",
			b: "6"
		},
	}
]
clevertap.upload(data).then((res) => {
	console.log(res)
})
