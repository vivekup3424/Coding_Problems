export const config = {
  host: process.env.HOST ?? "0.0.0.0",
  port: Number(process.env.PORT ?? 6969),
  mongodbUri: process.env.MONGODB_URI ?? "mongodb://localhost:27017/better_auth",
  betterAuthUrl: process.env.BETTER_AUTH_URL ?? "http://localhost:6969",
  betterAuthSecret: process.env.BETTER_AUTH_SECRET,
  googleClientId: process.env.GOOGLE_CLIENT_ID,
  googleClientSecret: process.env.GOOGLE_CLIENT_SECRET,
  trustedOrigins: (process.env.TRUSTED_ORIGINS ?? "http://localhost:5173")
    .split(",")
    .map((origin) => origin.trim())
    .filter(Boolean),
};

export type Config = typeof config;
