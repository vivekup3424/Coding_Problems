import { AccessToken } from 'livekit-server-sdk';

const roomName = 'red-room';
const participantName = 'john-doe';

const at = new AccessToken('APIEeDkRRrjEn5J', 'IAhfcCHMaQyruClhLAthMPKySK1qdVbNzYVYa7GKYcW', {
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