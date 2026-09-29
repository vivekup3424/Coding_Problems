import type { AuthSession } from "../../domain/auth-session.js";
import type { SessionProvider } from "../../application/ports/session-provider.js";
import type { Auth } from "./better-auth.js";

export class BetterAuthSessionProvider implements SessionProvider {
  private readonly auth: Auth;

  constructor({ auth }: { auth: Auth }) {
    this.auth = auth;
  }

  async getSession(headers: Headers): Promise<AuthSession | null> {
    const result = await this.auth.api.getSession({ headers });
    if (!result) return null;

    const { user, session } = result;
    return {
      user: {
        id: user.id,
        email: user.email,
        name: user.name,
        emailVerified: user.emailVerified,
        image: user.image ?? null,
        createdAt: user.createdAt,
      },
      session: {
        id: session.id,
        userId: session.userId,
        expiresAt: session.expiresAt,
      },
    };
  }
}
