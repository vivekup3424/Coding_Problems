import axios from "axios";
import fs from "fs";
import path from "path";

const CLEVERTAP_BASE_URL = "https://api.clevertap.com/1";

const headers = {
  "X-CleverTap-Account-Id": "8WW-K48-867Z",
  "X-CleverTap-Passcode": "SCW-RAW-CEEL",
  "Content-Type": "application/json",
};

const BATCH_SIZE = 100;

function readPhoneNumbers(): string[] {
  const raw = fs.readFileSync(path.join(__dirname, "test_users.csv"), "utf-8");
  const lines = raw.trim().split("\n").slice(1); // skip header
  const unique = [
    ...new Set(lines.map((l) => l.trim()).filter(Boolean)),
  ];
  return unique.map((num) => (num.startsWith("+") ? num : `+${num}`));
}

async function uploadBatch(identities: string[]): Promise<void> {
  const ts = Math.floor(Date.now() / 1000);
  const d = identities.map((identity) => ({
    identity,
    ts,
    type: "profile",
    profileData: { is_test_user: "Yes" },
  }));

  const res = await axios.post(`${CLEVERTAP_BASE_URL}/upload`, { d }, { headers });
  console.log(`  → ${JSON.stringify(res.data)}`);
}

async function main(): Promise<void> {
  const phones = readPhoneNumbers();
  console.log(`Loaded ${phones.length} unique phone numbers`);

  const totalBatches = Math.ceil(phones.length / BATCH_SIZE);

  for (let i = 0; i < phones.length; i += BATCH_SIZE) {
    const batch = phones.slice(i, i + BATCH_SIZE);
    const batchNum = Math.floor(i / BATCH_SIZE) + 1;
    console.log(`Batch ${batchNum}/${totalBatches} (${batch.length} users)...`);

    try {
      await uploadBatch(batch);
    } catch (err) {
      if (axios.isAxiosError(err)) {
        console.error(`  Batch ${batchNum} failed:`, err.response?.data ?? err.message);
      } else {
        throw err;
      }
    }

    // small pause between batches to stay within CleverTap rate limits
    if (i + BATCH_SIZE < phones.length) {
      await new Promise((r) => setTimeout(r, 500));
    }
  }

  console.log("Done.");
}

main().catch((err) => {
  console.error("Fatal:", err);
  process.exit(1);
});
