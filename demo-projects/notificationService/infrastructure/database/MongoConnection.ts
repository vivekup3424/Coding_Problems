import mongoose from 'mongoose';

/**
 * MongoDB connection manager
 */
export class MongoConnection {
  private static instance: MongoConnection;
  private isConnected: boolean = false;
  private connectionTimeout: number = 10000; // 10 seconds timeout
  
  private constructor() {}
  
  /**
   * Get a singleton instance of the MongoDB connection manager
   */
  public static getInstance(): MongoConnection {
    if (!MongoConnection.instance) {
      MongoConnection.instance = new MongoConnection();
    }
    return MongoConnection.instance;
  }
  
  /**
   * Check if the connection is established
   */
  public isConnectedToDb(): boolean {
    return this.isConnected && mongoose.connection.readyState === 1;
  }
  
  /**
   * Initialize the MongoDB connection with timeout
   * @param uri MongoDB connection URI
   */
  public async connect(uri: string): Promise<void> {
    try {
      console.log(`Connecting to MongoDB at ${uri}...`);
      
      // Set connection options
      const options = {
        serverSelectionTimeoutMS: this.connectionTimeout,
        connectTimeoutMS: this.connectionTimeout,
        socketTimeoutMS: this.connectionTimeout,
      };
      
      // Set up connection and error handling
      mongoose.connection.on('connected', () => {
        console.log('MongoDB connection established successfully');
        this.isConnected = true;
      });
      
      mongoose.connection.on('error', (err) => {
        console.error('MongoDB connection error:', err);
        this.isConnected = false;
      });
      
      mongoose.connection.on('disconnected', () => {
        console.log('MongoDB connection disconnected');
        this.isConnected = false;
      });
      
      // Connect with timeout
      await Promise.race([
        mongoose.connect(uri, options),
        new Promise((_, reject) => 
          setTimeout(() => reject(new Error('Connection timeout')), this.connectionTimeout)
        )
      ]);
      
      this.isConnected = true;
    } catch (error) {
      console.error('Failed to connect to MongoDB:', error);
      this.isConnected = false;
      throw error;
    }
  }
  
  /**
   * Disconnect from MongoDB
   */
  public async disconnect(): Promise<void> {
    if (!this.isConnected) {
      console.log('No active MongoDB connection to close');
      return;
    }
    
    try {
      await mongoose.disconnect();
      console.log('Disconnected from MongoDB');
      this.isConnected = false;
    } catch (error) {
      console.error('Error disconnecting from MongoDB:', error);
      throw error;
    }
  }
}
