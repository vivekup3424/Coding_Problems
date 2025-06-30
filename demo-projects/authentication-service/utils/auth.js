const jwt = require("jsonwebtoken");
const bcrypt = require("bcryptjs");

class AuthUtils {
  constructor() {
    this.jwtSecret = process.env.JWT_SECRET || "your-super-secret-jwt-key-change-in-production";
    this.jwtExpiresIn = process.env.JWT_EXPIRES_IN || "24h";
    this.saltRounds = 12;
  }

  /**
   * Hash a password using bcrypt
   * @param {string} password - Plain text password
   * @returns {Promise<string>} - Hashed password
   */
  async hashPassword(password) {
    return await bcrypt.hash(password, this.saltRounds);
  }

  /**
   * Compare a plain text password with a hashed password
   * @param {string} password - Plain text password
   * @param {string} hashedPassword - Hashed password
   * @returns {Promise<boolean>} - Whether passwords match
   */
  async comparePassword(password, hashedPassword) {
    return await bcrypt.compare(password, hashedPassword);
  }

  /**
   * Generate a JWT token
   * @param {object} payload - Token payload
   * @param {string} expiresIn - Token expiration
   * @returns {string} - JWT token
   */
  generateToken(payload, expiresIn = this.jwtExpiresIn) {
    return jwt.sign(payload, this.jwtSecret, { expiresIn });
  }

  /**
   * Verify and decode a JWT token
   * @param {string} token - JWT token
   * @returns {object} - Decoded token payload
   */
  verifyToken(token) {
    try {
      return jwt.verify(token, this.jwtSecret);
    } catch (error) {
      throw new Error("Invalid or expired token");
    }
  }

  /**
   * Extract token from Authorization header
   * @param {string} authHeader - Authorization header value
   * @returns {string|null} - Extracted token or null
   */
  extractTokenFromHeader(authHeader) {
    if (!authHeader || !authHeader.startsWith("Bearer ")) {
      return null;
    }
    return authHeader.substring(7);
  }

  /**
   * Generate a secure random string for API keys, session IDs, etc.
   * @param {number} length - Length of the random string
   * @returns {string} - Random string
   */
  generateSecureRandom(length = 32) {
    const chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    let result = "";
    for (let i = 0; i < length; i++) {
      result += chars.charAt(Math.floor(Math.random() * chars.length));
    }
    return result;
  }
}

module.exports = new AuthUtils();
