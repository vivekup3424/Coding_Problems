import { MongoClient } from "mongodb";

class MongoClientAdapter{
    client: MongoClient

    constructor(){
        this.client = new MongoClient("mongodb://localhost:27017")
    }
    
    start(){
        return this.client.connect()
    }
}

export const mongoInstance = new MongoClientAdapter()