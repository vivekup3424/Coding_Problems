import type { AuthSession } from "../../domain/auth-session.js";
import type { SessionProvider } from "../ports/session-provider.js";

export class GetCurrentSession {
  private readonly sessionProvider: SessionProvider;

  constructor({ sessionProvider }: { sessionProvider: SessionProvider }) {
    this.sessionProvider = sessionProvider;
  }

  execute(headers: Headers): Promise<AuthSession | null> {
    return this.sessionProvider.getSession(headers);
  }
}
