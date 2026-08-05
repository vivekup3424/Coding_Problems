import "dotenv/config";
import express from "express";
import cors from "cors";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { toNodeHandler } from "better-auth/node";
import { auth } from "./auth.js";

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const app = express();

app.use(
  cors({
    origin: process.env.BETTER_AUTH_URL,
    credentials: true,
  }),
);

// Better Auth must be mounted before express.json() so it can read the raw body.
app.all("/api/auth/{*any}", toNodeHandler(auth));

app.use(express.json());
app.use(express.static(path.join(__dirname, "../public")));

// Example protected route using the session.
app.get("/api/me", async (req, res) => {
  const session = await auth.api.getSession({
    headers: new Headers(
      Object.entries(req.headers).map(([k, v]) => [k, String(v ?? "")]),
    ),
  });

  if (!session) {
    res.status(401).json({ error: "Not authenticated" });
    return;
  }

  res.json(session);
});

const PORT = process.env.PORT ?? 3000;
app.listen(PORT, () => {
  console.log(`Better Auth PoC running at http://localhost:${PORT}`);
});
