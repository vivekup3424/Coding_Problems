import axios from "axios";
import path from "path";
import { GoogleAuth } from "google-auth-library";

interface FCMNotification {
  title: string;
  body: string;
  image?: string;
}

interface FCMAndroidNotification {
  title?: string;
  body?: string;
  image?: string;
}

interface FCMAndroidConfig {
  notification?: FCMAndroidNotification;
}

interface FCMMessage {
  to: string;
  notification: FCMNotification;
  android?: FCMAndroidConfig;
  data?: Record<string, string>;
}

export interface FCMResponse {
  name: string; // projects/{project_id}/messages/{message_id}
}

const FCM_PROJECT_ID = "keussc-7ceda";
const fcmAuth = new GoogleAuth({
  keyFile: path.join(__dirname, "../service-account.json"),
  scopes: "https://www.googleapis.com/auth/firebase.messaging",
});

export async function sendPushNotificationViaFCM(
  fcmToken: string,
  title: string,
  body: string,
  data?: Record<string, string>,
  imageUrl?: string
): Promise<FCMResponse> {
  const notification: FCMNotification = { title, body, ...(imageUrl && { image: imageUrl }) };
  const message: FCMMessage = {
    to: fcmToken,
    notification,
    ...(imageUrl && {
      android: {
        notification: { title, body, image: imageUrl },
      },
    }),
    ...(data && { data }),
  };

  const accessToken = await fcmAuth.getAccessToken();

  try {
    const res = await axios.post(
      `https://fcm.googleapis.com/v1/projects/${FCM_PROJECT_ID}/messages:send`,
      {
        message: {
          token: message.to,
          notification: message.notification,
          android: message.android,
          data: message.data,
        },
      },
      {
        headers: {
          Authorization: `Bearer ${accessToken}`,
          "Content-Type": "application/json",
        },
      }
    );
    const result = res.data as FCMResponse;
    console.log("FCM notification sent:", result.name);
    return result;
  } catch (err) {
    if (axios.isAxiosError(err)) {
      console.error("FCM request error:", err.response?.data ?? err.message);
    }
    throw err;
  }
}
