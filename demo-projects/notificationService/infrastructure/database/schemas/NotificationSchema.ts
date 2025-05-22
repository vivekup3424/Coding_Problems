import mongoose, { Schema } from 'mongoose';
import { NotificationStatus, Criticality } from '../../../models/notification';

// Define the Notification schema for MongoDB
const NotificationSchema = new Schema({
  id: { type: String, required: true, unique: true },
  templateId: { type: String, required: true },
  subscriberId: { type: String, required: false },
  topicId: { type: String, required: false },
  provider: { 
    type: String, 
    required: true,
    enum: ['sms', 'push', 'email'] 
  },
  payload: { 
    type: Schema.Types.Mixed, 
    required: true 
  },
  status: { 
    type: String, 
    enum: Object.values(NotificationStatus),
    default: NotificationStatus.PENDING
  },
  criticality: { 
    type: String, 
    enum: Object.values(Criticality),
    required: true
  },
  createdAt: { 
    type: Date, 
    default: Date.now 
  },
  updatedAt: { 
    type: Date, 
    default: Date.now 
  },
  readAt: { 
    type: Date, 
    required: false 
  },
  clientData: {
    deviceId: { type: String, required: false },
    readReceipt: { type: Boolean, required: false },
    clientTimestamp: { type: Number, required: false },
  }
}, { 
  timestamps: { createdAt: 'createdAt', updatedAt: 'updatedAt' },
  versionKey: false
});

// Create and export the Mongoose model
export const NotificationModel = mongoose.models.Notification || 
  mongoose.model('Notification', NotificationSchema);
