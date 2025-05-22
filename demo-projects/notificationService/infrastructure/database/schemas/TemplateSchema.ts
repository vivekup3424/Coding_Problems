import mongoose, { Schema } from 'mongoose';

// Define the Template schema for MongoDB
const TemplateSchema = new Schema({
  id: { type: String, required: true, unique: true },
  name: { type: String, required: true },
  description: { type: String },
  type: { 
    type: String, 
    enum: ['email', 'sms', 'push'],
    required: true
  },
  content: { type: String, required: true },
  variables: { type: [String], default: [] },
  version: { type: Number, default: 1 },
  isActive: { type: Boolean, default: true },
  createdAt: { type: Date, default: Date.now },
  updatedAt: { type: Date, default: Date.now }
}, { 
  timestamps: { createdAt: 'createdAt', updatedAt: 'updatedAt' },
  versionKey: false
});

// Create and export the Mongoose model
export const TemplateModel = mongoose.models.Template || 
  mongoose.model('Template', TemplateSchema);
