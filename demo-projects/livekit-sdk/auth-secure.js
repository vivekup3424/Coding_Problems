import { AccessToken } from 'livekit-server-sdk';
import dotenv from 'dotenv';

// Load environment variables
dotenv.config();

const roomName = 'red-room';
const participantName = 'john-doe';

// Use environment variables for security
const apiKey = process.env.LIVEKIT_API_KEY;
const apiSecret = process.env.LIVEKIT_API_SECRET;

if (!apiKey || !apiSecret) {
  throw new Error('LIVEKIT_API_KEY and LIVEKIT_API_SECRET must be set in environment variables');
}

const at = new AccessToken(apiKey, apiSecret, {
  identity: participantName,
});

// Add video grant to allow room joining
at.addGrant({
  roomJoin: true,
  room: roomName,
  canPublish: true,
  canSubscribe: true,
});

const token = await at.toJwt();
console.log('Access token:', token);

export { token };
