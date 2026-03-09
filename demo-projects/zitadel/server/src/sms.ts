import express from 'express';

const app = express();

app.use(express.json());

const port = process.env.PORT || 3001;

app.post('/akhil', (req, res) => {
    console.log("SMS payload:", req.body); // ✅ This shows the actual data from ZITADEL
    res.status(200).send('OK');
});

app.all("/zitadel-code", (req, res) => {
    console.log("CODE payload:", req.body, req.params); // ✅ This shows the actual data from ZITADEL
    // Here you can handle the SMS payload as needed
    res.status(200).send('OK');
});

app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});