import type { AuthSession } from "../../domain/auth-session.js";

export interface SessionProvider {
  getSession(headers: Headers): Promise<AuthSession | null>;
}
