require("dotenv").config();
const axios = require("axios");

const endpoint = "https://api.clevertap.com/1/send/push.json";
const payload = {
  to: {
    // Identity: ["+919740303762"]
    Identity: ["+919553014924"]
    // Identity: ["+918247781785"]
  },
  "name": "My API Campaign",
  "estimate_only": true,
  "target_mode": "push",
  "where": {
    "event_name": "Charged",
    "from": 20250707,
    "to": 20350303
  },
  "respect_frequency_caps": false,
  "ttl": {
    "ttl_type": "absolute",
    "value": 202207200000
  },
  "content": {
    "title": "Hi!",
    "body": "How are you doing today?",
    "platform_specific": {
      "android": {
        "enable_rendermax": true,
        "wzrk_cid": "Marketing",
        "background_image": "https://static.vecteezy.com/system/resources/thumbnails/001/971/264/small_2x/beautiful-cherry-blossom-with-bokeh-lights-background-concept-free-vector.jpg",
        "default_sound": true,
        "Key": "Value_android"
      }
    }
  },
  "devices": [
    "android"
  ],
  "users_limit_overall": 101,
  "when": {
    "type": "now",
    "delivery_timezone": "user",
    "user_timezone_wrap_around": true
  }
};
const headers = {
  "X-CleverTap-Account-Id": process.env.CLEVERTAP_ACCOUNT_ID,
  "X-CleverTap-Passcode": process.env.CLEVERTAP_ACCOUNT_PASSCODE,
  "Content-Type": "application/json",
};

axios.post(endpoint, payload, { headers })
  .then(res => console.log("CleverTap response:", res.data))
  .catch(err => console.error("Error:", err));