import { AccessToken } from 'livekit-server-sdk';

const apiKey = 'your-api-key';
const apiSecret = 'your-api-secret';

// Example 1: Full participant (can publish and subscribe)
function createFullParticipantToken(participantName, roomName) {
  const at = new AccessToken(apiKey, apiSecret, {
    identity: participantName,
  });
  
  at.addGrant({
    roomJoin: true,
    room: roomName,
    canPublish: true,      // Can share camera/mic
    canSubscribe: true,    // Can see/hear others
    canPublishData: true,  // Can send chat messages
  });
  
  return at.toJwt();
}

// Example 2: View-only participant (observer)
function createViewerToken(participantName, roomName) {
  const at = new AccessToken(apiKey, apiSecret, {
    identity: participantName,
  });
  
  at.addGrant({
    roomJoin: true,
    room: roomName,
    canPublish: false,     // Cannot share camera/mic
    canSubscribe: true,    // Can see/hear others
    canPublishData: false, // Cannot send messages
  });
  
  return at.toJwt();
}

// Example 3: Moderator/Admin
function createModeratorToken(participantName, roomName) {
  const at = new AccessToken(apiKey, apiSecret, {
    identity: participantName,
  });
  
  at.addGrant({
    roomJoin: true,
    room: roomName,
    roomAdmin: true,       // Can manage the room
    canPublish: true,
    canSubscribe: true,
    canPublishData: true,
    roomRecord: true,      // Can record the session
  });
  
  return at.toJwt();
}

// Example 4: Hidden participant (like a recording bot)
function createHiddenParticipantToken(participantName, roomName) {
  const at = new AccessToken(apiKey, apiSecret, {
    identity: participantName,
  });
  
  at.addGrant({
    roomJoin: true,
    room: roomName,
    hidden: true,          // Won't appear in participant list
    canSubscribe: true,    // Can receive all tracks
    recorder: true,        // Special recording permissions
  });
  
  return at.toJwt();
}

// Example 5: Guest with limited time access
function createGuestToken(participantName, roomName) {
  const at = new AccessToken(apiKey, apiSecret, {
    identity: participantName,
  });
  
  // Set token to expire in 1 hour
  at.ttl = '1h';
  
  at.addGrant({
    roomJoin: true,
    room: roomName,
    canPublish: false,     // Guests can't publish
    canSubscribe: true,    // But can watch
    canPublishData: true,  // Can send chat messages
  });
  
  return at.toJwt();
}

// Example 6: Wildcard room access (be careful with this!)
function createMultiRoomToken(participantName) {
  const at = new AccessToken(apiKey, apiSecret, {
    identity: participantName,
  });
  
  at.addGrant({
    roomJoin: true,
    // No specific room - can join any room
    roomList: true,        // Can list available rooms
    canPublish: true,
    canSubscribe: true,
  });
  
  return at.toJwt();
}

export {
  createFullParticipantToken,
  createViewerToken,
  createModeratorToken,
  createHiddenParticipantToken,
  createGuestToken,
  createMultiRoomToken
};
