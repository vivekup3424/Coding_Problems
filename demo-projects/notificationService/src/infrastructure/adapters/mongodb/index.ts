import { MongoClient } from "mongodb";
const MONGO_URI = process.env.MONGO_URI || "mongodb://localhost:27017";

class MongoClientAdapter {
    client: MongoClient;
    constructor() {
        this.client = new MongoClient(MONGO_URI)
    }
    start() {
        return this.client.connect().then(() => {
            console.log("MongoDB connected successfully");
        }).catch((error) => {
            console.error("MongoDB connection failed:", error);
            throw error;
        });
    }
}

export const mongoClientAdapter = new MongoClientAdapter();