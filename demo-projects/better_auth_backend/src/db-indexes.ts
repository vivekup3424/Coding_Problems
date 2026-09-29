import type { Db, IndexDescription } from "mongodb";

// better-auth's MongoDB adapter creates collections on first write but no indexes,
// so uniqueness and the per-request session lookup rely on these.
const indexes: Record<string, IndexDescription[]> = {
  user: [
    { key: { email: 1 }, name: "email_unique", unique: true },
    {
      key: { phoneNumber: 1 },
      name: "phoneNumber_unique",
      unique: true,
      // Google-only users have no phone number.
      partialFilterExpression: { phoneNumber: { $type: "string" } },
    },
  ],
  session: [
    { key: { token: 1 }, name: "token_unique", unique: true },
    { key: { userId: 1 }, name: "userId" },
    { key: { expiresAt: 1 }, name: "expiresAt_ttl", expireAfterSeconds: 0 },
  ],
  account: [
    { key: { providerId: 1, accountId: 1 }, name: "provider_account_unique", unique: true },
    { key: { userId: 1 }, name: "userId" },
  ],
  verification: [
    { key: { identifier: 1 }, name: "identifier" },
    { key: { expiresAt: 1 }, name: "expiresAt_ttl", expireAfterSeconds: 0 },
  ],
};

// Idempotent: createIndexes is a no-op for indexes that already exist with the same spec.
export async function ensureIndexes(db: Db): Promise<void> {
  for (const [collection, specs] of Object.entries(indexes)) {
    await db.collection(collection).createIndexes(specs);
  }
}
