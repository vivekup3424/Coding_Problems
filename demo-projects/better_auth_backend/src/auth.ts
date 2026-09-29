import { betterAuth } from "better-auth";
import { mongodbAdapter } from "better-auth/adapters/mongodb";
import { phoneNumber } from "better-auth/plugins";
import type { Db, MongoClient } from "mongodb";
import type { Config } from "./config.js";
import type { SmsSender } from "./sms.js";

// E.164, e.g. +919876543210
const E164 = /^\+[1-9]\d{7,14}$/;

export function createAuth({
  config,
  mongoClient,
  mongoDb,
  smsSender,
}: {
  config: Config;
  mongoClient: MongoClient;
  mongoDb: Db;
  smsSender: SmsSender;
}) {
  if (!config.googleClientId || !config.googleClientSecret) {
    throw new Error("GOOGLE_CLIENT_ID and GOOGLE_CLIENT_SECRET must be set");
  }

  return betterAuth({
    database: mongodbAdapter(mongoDb, {
      client: mongoClient,
      // Transactions need a replica set; the local docker-compose MongoDB is standalone.
      transaction: false,
    }),
    baseURL: config.betterAuthUrl,
    secret: config.betterAuthSecret,
    trustedOrigins: config.trustedOrigins,
    socialProviders: {
      google: {
        clientId: config.googleClientId,
        clientSecret: config.googleClientSecret,
      },
    },
    plugins: [
      phoneNumber({
        phoneNumberValidator: (number) => E164.test(number),
        sendOTP: ({ phoneNumber, code }) =>
          smsSender.send(phoneNumber, `Your verification code is ${code}`),
        // Create the user on first successful verification. better-auth requires
        // an email, so phone-only users get a placeholder on the reserved .invalid TLD.
        signUpOnVerification: {
          getTempEmail: (number) => `${number.slice(1)}@phone.invalid`,
          getTempName: (number) => number,
        },
      }),
    ],
  });
}

export type Auth = ReturnType<typeof createAuth>;
