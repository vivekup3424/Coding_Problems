#!/usr/bin/env node

/**
 * Simple HTTPS server for testing Firebase Cloud Messaging
 * This is needed because service workers require HTTPS
 */

const express = require('express');
const https = require('https');
const fs = require('fs');
const path = require('path');

const app = express();
const PORT = process.env.PORT || 3000;

// Serve static files from src directory
app.use(express.static(path.join(__dirname, 'src')));
app.use('/public', express.static(path.join(__dirname, 'public')));

// Fallback to index.html for SPA routing
app.get('*', (req, res) => {
    res.sendFile(path.join(__dirname, 'src', 'index.html'));
});

// Check if we have SSL certificates
const certPath = path.join(__dirname, 'ssl', 'cert.pem');
const keyPath = path.join(__dirname, 'ssl', 'key.pem');

if (fs.existsSync(certPath) && fs.existsSync(keyPath)) {
    // HTTPS server
    const options = {
        cert: fs.readFileSync(certPath),
        key: fs.readFileSync(keyPath)
    };
    
    https.createServer(options, app).listen(PORT, () => {
        console.log(`🚀 HTTPS Server running at https://localhost:${PORT}`);
        console.log('🔒 Using SSL certificates for secure service worker registration');
    });
} else {
    // HTTP server (development only)
    app.listen(PORT, () => {
        console.log(`🚀 HTTP Server running at http://localhost:${PORT}`);
        console.log('⚠️  Using HTTP - service workers may not work properly');
        console.log('💡 For production, use HTTPS or generate SSL certificates');
        console.log('');
        console.log('To generate self-signed certificates:');
        console.log('mkdir ssl && cd ssl');
        console.log('openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -days 365 -nodes');
    });
}
