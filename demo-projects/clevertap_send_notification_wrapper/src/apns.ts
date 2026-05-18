import path from "path";
import apn from "@parse/node-apn";

const APNS_CONFIG = {
  keyFile: path.join(__dirname, "../apns-auth-key.p8"),
  keyId: "U74DW39736",
  teamId: "97B64EW8V8",
  bundleId: "com.keus.app.flutter.dev",
  production: false,
};

export interface APNsResult {
  token: string;
  status: "sent" | "failed";
  error?: string;
}

export async function sendPushNotificationViaAPNs(
  tokens: string[],
  title: string,
  body: string,
  options?: {
    subtitle?: string;
    mediaUrl?: string;
    data?: Record<string, string>;
  }
): Promise<APNsResult[]> {
  const provider = new apn.Provider({
    token: {
      key: APNS_CONFIG.keyFile,
      keyId: APNS_CONFIG.keyId,
      teamId: APNS_CONFIG.teamId,
    },
    production: APNS_CONFIG.production,
  });

  const notification = new apn.Notification();
  notification.alert = { title, body, ...(options?.subtitle && { subtitle: options.subtitle }) };
  notification.sound = "default";
  notification.topic = APNS_CONFIG.bundleId;

  if (options?.mediaUrl) {
    notification.mutableContent = true;
    notification.payload = { ...notification.payload, "attachment-url": options.mediaUrl };
  }

  if (options?.data) {
    notification.payload = { ...notification.payload, ...options.data };
  }

  const results: APNsResult[] = [];

  for (const token of tokens) {
    try {
      const response = await provider.send(notification, token);
      if (response.failed.length > 0) {
        const failure = response.failed[0];
        const errMsg = failure?.error?.message ?? failure?.response?.reason ?? "unknown";
        console.error(`APNs failed for token ${token.slice(0, 8)}...: ${errMsg}`);
        results.push({ token, status: "failed", error: errMsg });
      } else {
        console.log(`APNs notification sent to token ${token.slice(0, 8)}...`);
        results.push({ token, status: "sent" });
      }
    } catch (err) {
      const errMsg = err instanceof Error ? err.message : String(err);
      console.error(`APNs error for token ${token.slice(0, 8)}...: ${errMsg}`);
      results.push({ token, status: "failed", error: errMsg });
    }
  }

  provider.shutdown();
  return results;
}
