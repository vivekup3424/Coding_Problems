import mongoose, { Schema } from 'mongoose';

// Define the Subscriber schema for MongoDB
const SubscriberSchema = new Schema({
  id: { type: String, required: true, unique: true },
  firstName: { type: String, required: true },
  lastName: { type: String, required: true },
  email: { type: String, required: false },
  phoneNumber: { type: String, required: false },
  pushTokens: { type: [String], default: [] },
  topics: { type: [String], default: [] },
  createdAt: { type: Date, default: Date.now },
  updatedAt: { type: Date, default: Date.now }
}, { 
  timestamps: { createdAt: 'createdAt', updatedAt: 'updatedAt' },
  versionKey: false
});

// Create and export the Mongoose model
export const SubscriberModel = mongoose.models.Subscriber || 
  mongoose.model('Subscriber', SubscriberSchema);
