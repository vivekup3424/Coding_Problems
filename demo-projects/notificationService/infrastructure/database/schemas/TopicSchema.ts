import mongoose, { Schema } from 'mongoose';

// Define the Topic schema for MongoDB
const TopicSchema = new Schema({
  id: { type: String, required: true, unique: true },
  name: { type: String, required: true },
  description: { type: String },
  subscribers: { type: [String], default: [] },
  createdAt: { type: Date, default: Date.now },
  updatedAt: { type: Date, default: Date.now }
}, { 
  timestamps: { createdAt: 'createdAt', updatedAt: 'updatedAt' },
  versionKey: false
});

// Create and export the Mongoose model
export const TopicModel = mongoose.models.Topic || 
  mongoose.model('Topic', TopicSchema);
