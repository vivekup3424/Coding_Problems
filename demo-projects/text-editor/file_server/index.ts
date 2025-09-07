import express from "express";
import path from "path";
import { fileURLToPath } from 'url';
const app = express();
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);
app.use(express.static(path.join(__dirname, "../frontend")))

const port = 8745;
app.listen(port, () => {
  console.log(`File server is running at http://localhost:${port}`);
});