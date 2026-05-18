import axios from "axios";
import { sendPushNotificationViaFCM } from "./fcm";
import { sendPushNotificationViaAPNs } from "./apns";
import fs from "fs";
const CLEVERTAP_BASE_URL = "https://api.clevertap.com/1";

interface CleverTapHeaders extends Record<string, string> {
  "X-CleverTap-Account-Id": string;
  "X-CleverTap-Passcode": string;
  "Content-Type": string;
}

export interface CleverTapPushData {
  to: {
    Identity?: string[];
    ObjectId?: string[];
    Email?: string[];
  };
  target_mode: "push";
  content: {
    title: string;
    body: string;
    imageUrl?: string;
    deep_link?: string;
    badge_icon?: string;
    platform_specific?: {
      android?: {
        large_icon?: string;
        wzrk_cid?: string;
        background_image?: string;
        params?: string;
      };
      ios?: {
        ct_mediaUrl?: string;
        sound_file?: string;
        "mutable-content"?: string;
        params?: string;
      };
    };
  };
  ttl?: {
    ttl_type: "relative";
    value: number;
  };
}

interface CleverTapApiResponse {
  status: string;
  processed: number;
  unprocessed: unknown[];
}


interface PlatformInfo {
  objectId: string;
  platform: string;
  push_token?: string;
  [key: string]: unknown;
}

interface UserProfileRecord {
  platformInfo: PlatformInfo[];
  identity: string;
  [key: string]: unknown;
}

interface UserProfileResponse {
  status: string;
  record: UserProfileRecord;
}

interface CampaignProfileField {
  name: string;
  operator: string;
  value: string;
}

interface CampaignWhere {
  common_profile_properties?: {
    profile_fields: CampaignProfileField[];
  };
}

interface CampaignContent {
  title: string;
  body: string;
  deep_link?: string;
}

interface CreateCampaignPayload {
  name: string;
  target_mode: string;
  estimate_only?: boolean;
  where?: CampaignWhere;
  send_to_all_devices?: boolean;
  devices?: string[];
  when: string;
  content: CampaignContent;
}

interface CreateCampaignResponse {
  status: string;
  id?: number;
  estimates?: unknown;
}


const headers: CleverTapHeaders = {
  "X-CleverTap-Account-Id": "48Z-548-4R7Z",
  "X-CleverTap-Passcode": "AYK-JAW-AWEL",
  "Content-Type": "application/json",
};

async function sendPushNotification(
  payload: CleverTapPushData
): Promise<CleverTapApiResponse> {
  try {
    const res = await axios.post(
      `${CLEVERTAP_BASE_URL}/send/push.json`,
      payload,
      { headers }
    );
    const data = res.data as CleverTapApiResponse;
    console.log("Push notification sent successfully:", data);
    return data;
  } catch (err) {
    if (axios.isAxiosError(err)) {
      console.error("Error sending push notification:", err.response?.data ?? err.message);
    }
    throw err;
  }
}

async function createCampaign(
  payload: CreateCampaignPayload
): Promise<CreateCampaignResponse> {
  try {
    const res = await axios.post(
      `${CLEVERTAP_BASE_URL}/targets/create.json`,
      payload,
      { headers }
    );
    const data = res.data as CreateCampaignResponse;
    console.log("Campaign created successfully:", data);
    return data;
  } catch (err) {
    if (axios.isAxiosError(err)) {
      console.error("Error creating campaign:", err.response?.data ?? err.message);
    }
    throw err;
  }
}

async function getUserProfile(identity: string): Promise<UserProfileResponse> {
  try {
    const res = await axios.get(
      `${CLEVERTAP_BASE_URL}/profile.json?identity=${encodeURIComponent(identity)}`,
      { headers }
    );
    return res.data as UserProfileResponse;
  } catch (error) {
    if (axios.isAxiosError(error)) {
      console.error("Error fetching user profile:", error.response?.data ?? error.message);
    }
    throw error;
  }
}

interface CleverTapEvent {
  identity: string;
  ts: number;
  type: "event";
  evtName: string;
  evtData?: Record<string, unknown>;
}

interface UploadEventsResponse {
  status: string;
  processed: number;
  unprocessed: unknown[];
}

async function uploadEvents(events: CleverTapEvent[]): Promise<UploadEventsResponse> {
  try {
    const res = await axios.post(
      `${CLEVERTAP_BASE_URL}/upload`,
      { d: events },
      { headers }
    );
    const data = res.data as UploadEventsResponse;
    console.log("Events uploaded:", data);
    return data;
  } catch (err) {
    if (axios.isAxiosError(err)) {
      console.error("Error uploading events:", err.response?.data ?? err.message);
    }
    throw err;
  }
}

function buildEvent(
  identity: string,
  evtName: string,
  evtData?: Record<string, unknown>
): CleverTapEvent {
  return {
    identity,
    ts: Math.floor(Date.now() / 1000),
    type: "event",
    evtName,
    ...(evtData && { evtData }),
  };
}

interface CleverTapProfile {
  identity: string;
  ts: number;
  type: "profile";
  profileData: Record<string, string | number | boolean>;
}

async function uploadUserProfile(
  identity: string,
  profileData: Record<string, string | number | boolean>
): Promise<UploadEventsResponse> {
  const profile: CleverTapProfile = {
    identity,
    ts: Math.floor(Date.now() / 1000),
    type: "profile",
    profileData,
  };
  try {
    const res = await axios.post(
      `${CLEVERTAP_BASE_URL}/upload`,
      { d: [profile] },
      { headers }
    );
    const data = res.data as UploadEventsResponse;
    console.log("Profile uploaded:", data);
    return data;
  } catch (err) {
    if (axios.isAxiosError(err)) {
      console.error("Error uploading profile:", err.response?.data ?? err.message);
    }
    throw err;
  }
}

function getAllObjectIdsForProfile(profile: UserProfileResponse): string[] {
  return profile.record.platformInfo.map((p) => p.objectId);
}

function getAllFCMTokensForProfile(profile: UserProfileResponse): string[] {
  const fcmTokens: string[] = [];
  for (const platform of profile.record.platformInfo) {
    if (platform.platform.toLowerCase() === "android" && platform.push_token) {
      const raw = platform.push_token;
      fcmTokens.push(raw.startsWith("fcm:") ? raw.slice(4) : raw);
    }
  }
  return fcmTokens;
}

function getAllAPNsTokensForProfile(profile: UserProfileResponse): string[] {
  const tokens: string[] = [];
  for (const platform of profile.record.platformInfo) {
    if (
      platform.platform.toLowerCase() === "ios" &&
      platform.push_token &&
      !platform.push_token.startsWith("fcm:")
    ) {
      tokens.push(platform.push_token);
    }
  }
  return tokens;
}


const NOTIFICATION_TITLE = "Hello from Keus";
const NOTIFICATION_SUBTITLE = "Smart Home Update";
const NOTIFICATION_BODY = "Your living room lights were turned on automatically.";
const NOTIFICATION_MEDIA_URL =
  "https://images.unsplash.com/photo-1558618666-fcd25c85cd64?w=600"; // replace with your own image
const TARGET_IDENTITY = "+916260863371";

async function main(): Promise<void> {
  const event = buildEvent(TARGET_IDENTITY, "gateway_notification", {
    title: "This one is from clevertap",
    body: "Testing direct FCM + APNs",
    subtitle: "This is the subtitle",
    imageUrl: "https://images.unsplash.com/photo-1558618666-fcd25c85cd64?w=600",
    channelId: "vdp_ring_channel_id",
    soundFile: "ring_sound.wav",
    deepLink: "app://home",
    params: JSON.stringify({
      applianceId: "6a04539db3615f88a18d765b",
      applianceName: "Testing Room",
      detectionData: {
        applianceId: "6a04539db3615f88a18d765b",
        eventId: "c7aaad40-66d1-4d03-a72a-eab57870cd0d",
        detectionType: 0,
        eventStartTime: 1778763455576,
        eventEndTime: 1778763463576,
        eventThumbnailId: "https://heimdall.keus.in/...",
      },
    }),
  });

  await uploadEvents([event]);
  // const fcmtoken = "eSZKtQesQ7-QREjcE2V83i:APA91bFEpXv5vWZvRFLie0E3B6s3zS5rsJ4iGNI-UhUuhk3XIFNCp3AlJvZ-srWqmCATiqk7fhpMNvRXMwOajFI2uR1YgGNrMECSLvNjr-75S2o_PuXPLDk";
  const fcmtoken = "e8vnmHuqSAKFF-8A7GH-lF:APA91bHAl34Zf3NnoZtpV23XK1jj89JMhWrBiYziADrcTdMjwKXrNcOPqbNI_1Tk0m7Rxg9j3TgGuoRdfzjhJM2m4DeRorpZayqX6HzqdtEHuY-zVLtx5vA"
  await sendPushNotificationViaFCM(
    fcmtoken,
    "this one is from direct FCM",
    NOTIFICATION_BODY,
    { customData: "This is some custom data for the notification" },
    NOTIFICATION_MEDIA_URL
  );
}

main().catch((err) => {
  console.error("Fatal error:", err);
  process.exit(1);
});
