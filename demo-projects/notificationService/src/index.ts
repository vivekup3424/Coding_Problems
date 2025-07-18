import { config } from "dotenv";
config();
console.log(process.env.MONGO_URI);