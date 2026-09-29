import { Router } from "express";
import { fromNodeHeaders } from "better-auth/node";
import type { Auth } from "../auth.js";

export function createMeRouter({ auth }: { auth: Auth }): Router {
  const router = Router();

  router.get("/", async (req, res) => {
    const result = await auth.api.getSession({
      headers: fromNodeHeaders(req.headers),
    });

    if (!result) {
      res.status(401).json({ error: "Not authenticated" });
      return;
    }

    // Don't send the session token back in the body.
    const { token: _token, ...session } = result.session;
    res.json({ user: result.user, session });
  });

  return router;
}
