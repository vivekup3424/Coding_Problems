import { Service, ServiceBroker, Context } from 'moleculer';
import * as jwt from 'jsonwebtoken';
import * as bcrypt from 'bcrypt';
import { readFileSync } from 'fs';
import { join } from 'path';
import { config } from '../config';
import { User } from '../types';

/**
 * Authentication Service
 * Handles user login, logout, and JWT token management
 */
export default class AuthenticationService extends Service {
  private users: { users: User[] } = { users: [] };

  public constructor(broker: ServiceBroker) {
    super(broker);
    this.parseServiceSchema({
      name: config.services.authentication.name,
      version: config.services.authentication.version,
      
      actions: {
        login: {
          rest: 'POST /login',
          params: {
            username: 'string',
            password: 'string'
          },
          handler: this.login
        },
        
        verify: {
          params: {
            token: 'string'
          },
          handler: this.verifyToken
        },
        
        getUserById: {
          params: {
            userId: 'string'
          },
          handler: this.getUserById
        }
      },
      
      started: this.serviceStarted
    });
  }

  /**
   * Service started lifecycle event handler
   */
  async serviceStarted(): Promise<void> {
    try {
      const userDataPath = join(process.cwd(), config.dataFiles.users);
      const userData = readFileSync(userDataPath, 'utf8');
      this.users = JSON.parse(userData);
      this.logger.info(`✅ Loaded ${this.users.users.length} users from ${userDataPath}`);
    } catch (error) {
      this.logger.error('❌ Failed to load user data:', error);
      throw error;
    }
  }

  /**
   * User login action
   */
  async login(ctx: Context<{ username: string; password: string }>): Promise<{ token: string; user: Partial<User> }> {
    const { username, password } = ctx.params;
    
    // Find user
    const user = this.users.users.find(u => u.username === username);
    if (!user) {
      throw new Error('Invalid credentials');
    }

    // Verify password
    const isValidPassword = await bcrypt.compare(password, user.passwordHash);
    if (!isValidPassword) {
      throw new Error('Invalid credentials');
    }

    // Generate JWT token
    const tokenPayload = {
      userId: user.id,
      username: user.username,
      profile: user.profile
    };

    const token = jwt.sign(tokenPayload, config.jwt.secret, {
      expiresIn: config.jwt.expiresIn,
      issuer: config.jwt.issuer,
      audience: config.jwt.audience
    } as jwt.SignOptions);

    // Return token and safe user data
    const safeUser = {
      id: user.id,
      username: user.username,
      email: user.email,
      profile: user.profile,
      createdAt: user.createdAt,
      lastLogin: new Date().toISOString()
    };

    this.logger.info(`🔐 User ${username} logged in successfully`);
    
    return { token, user: safeUser };
  }

  /**
   * Verify JWT token action
   */
  async verifyToken(ctx: Context<{ token: string }>): Promise<any> {
    try {
      const decoded = jwt.verify(ctx.params.token, config.jwt.secret, {
        issuer: config.jwt.issuer,
        audience: config.jwt.audience
      });
      return decoded;
    } catch (error) {
      throw new Error('Invalid token');
    }
  }

  /**
   * Get user by ID action
   */
  async getUserById(ctx: Context<{ userId: string }>): Promise<Partial<User> | null> {
    const user = this.users.users.find(u => u.id === ctx.params.userId);
    if (!user) {
      return null;
    }

    return {
      id: user.id,
      username: user.username,
      email: user.email,
      profile: user.profile,
      createdAt: user.createdAt,
      lastLogin: user.lastLogin
    };
  }
}
