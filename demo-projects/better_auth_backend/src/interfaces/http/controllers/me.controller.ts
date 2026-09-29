import type { Request, Response } from "express";
import type { GetCurrentSession } from "../../../application/use-cases/get-current-session.js";
import { toWebHeaders } from "../to-web-headers.js";

export class MeController {
  private readonly getCurrentSession: GetCurrentSession;

  constructor({ getCurrentSession }: { getCurrentSession: GetCurrentSession }) {
    this.getCurrentSession = getCurrentSession;
  }

  show = async (req: Request, res: Response) => {
    const session = await this.getCurrentSession.execute(toWebHeaders(req.headers));

    if (!session) {
      res.status(401).json({ error: "Not authenticated" });
      return;
    }

    res.json(session);
  };
}
