import jwt from 'jsonwebtoken';
import bcrypt from 'bcryptjs';

export interface TokenPayload {
  userId: string;
  email: string;
  roles: string[];
  [key: string]: any;
}

export class AuthUtils {
  private jwtSecret: string;
  private jwtExpiresIn: string;
  private saltRounds: number;

  constructor() {
    this.jwtSecret = process.env.JWT_SECRET || "your-super-secret-jwt-key-change-in-production";
    this.jwtExpiresIn = process.env.JWT_EXPIRES_IN || "24h";
    this.saltRounds = 12;
  }

  /**
   * Hash a password using bcrypt
   */
  async hashPassword(password: string): Promise<string> {
    return await bcrypt.hash(password, this.saltRounds);
  }

  /**
   * Compare a plain text password with a hashed password
   */
  async comparePassword(password: string, hashedPassword: string): Promise<boolean> {
    return await bcrypt.compare(password, hashedPassword);
  }

  /**
   * Generate a JWT token
   */
  generateToken(payload: TokenPayload, expiresIn: string = this.jwtExpiresIn): string {
    return jwt.sign(payload as object, this.jwtSecret, { expiresIn });
  }

  /**
   * Verify and decode a JWT token
   */
  verifyToken(token: string): TokenPayload {
    try {
      return jwt.verify(token, this.jwtSecret) as TokenPayload;
    } catch (error) {
      throw new Error("Invalid or expired token");
    }
  }

  /**
   * Extract token from Authorization header
   */
  extractTokenFromHeader(authHeader: string | undefined): string | null {
    if (!authHeader || !authHeader.startsWith("Bearer ")) {
      return null;
    }
    return authHeader.substring(7);
  }

  /**
   * Generate a secure random string for API keys, session IDs, etc.
   */
  generateSecureRandom(length: number = 32): string {
    const chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    let result = "";
    for (let i = 0; i < length; i++) {
      result += chars.charAt(Math.floor(Math.random() * chars.length));
    }
    return result;
  }
}

export default new AuthUtils();
