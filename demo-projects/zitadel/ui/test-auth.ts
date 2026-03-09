#!/usr/bin/env bun

/**
 * Test script for Zitadel PKCE authentication flow
 * This script demonstrates the server-side authentication flow
 */

// For Node.js environment
declare const process: any;

const DOMAIN = "https://auth.keus.in";
const CLIENT_ID = "325033819512045574";
const REDIRECT_URI = "http://localhost:3000/auth/callback";

// PKCE utility functions (copied from lib for testing)
function generateRandomString(length: number): string {
    const charset = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~';
    let result = '';
    const randomValues = new Uint8Array(length);
    crypto.getRandomValues(randomValues);

    for (let i = 0; i < length; i++) {
        result += charset.charAt(randomValues[i] % charset.length);
    }
    return result;
}

async function sha256(plain: string): Promise<ArrayBuffer> {
    const encoder = new TextEncoder();
    const data = encoder.encode(plain);
    return await crypto.subtle.digest('SHA-256', data);
}

function base64URLEncode(buffer: ArrayBuffer): string {
    const bytes = new Uint8Array(buffer);
    let binary = '';
    for (let i = 0; i < bytes.byteLength; i++) {
        binary += String.fromCharCode(bytes[i]);
    }
    return btoa(binary)
        .replace(/\+/g, '-')
        .replace(/\//g, '_')
        .replace(/=/g, '');
}

async function generatePKCE() {
    const codeVerifier = generateRandomString(128);
    const hashedVerifier = await sha256(codeVerifier);
    const codeChallenge = base64URLEncode(hashedVerifier);
    const state = generateRandomString(32);

    return {
        codeVerifier,
        codeChallenge,
        state
    };
}

async function exchangeCodeForTokens(code: string, codeVerifier: string) {
    const tokenData = new URLSearchParams({
        grant_type: 'authorization_code',
        code: code,
        redirect_uri: REDIRECT_URI,
        client_id: CLIENT_ID,
        code_verifier: codeVerifier
    });

    const response = await fetch(`${DOMAIN}/oauth/v2/token`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
        },
        body: tokenData
    });

    if (!response.ok) {
        const errorText = await response.text();
        throw new Error(`Token exchange failed: ${response.status} ${errorText}`);
    }

    return await response.json();
}

async function getUserInfo(accessToken: string) {
    const response = await fetch(`${DOMAIN}/oidc/v1/userinfo`, {
        headers: {
            'Authorization': `Bearer ${accessToken}`
        }
    });

    if (!response.ok) {
        const errorText = await response.text();
        throw new Error(`Failed to get user info: ${response.status} ${errorText}`);
    }

    return await response.json();
}

async function testPKCEGeneration() {
    console.log("🔑 Testing PKCE parameter generation...");

    try {
        const authState = await generatePKCE();
        console.log("✅ PKCE parameters generated successfully:");
        console.log(`   Code Verifier: ${authState.codeVerifier.substring(0, 20)}...`);
        console.log(`   Code Challenge: ${authState.codeChallenge}`);
        console.log(`   State: ${authState.state}`);
        console.log(`   Verifier Length: ${authState.codeVerifier.length}`);

        // Verify code challenge is base64url encoded
        const isValidBase64url = /^[A-Za-z0-9_-]+$/.test(authState.codeChallenge);
        console.log(`   Challenge Format Valid: ${isValidBase64url ? '✅' : '❌'}`);

        return authState;
    } catch (error) {
        console.error("❌ PKCE generation failed:", error);
        return null;
    }
}

function generateAuthorizationUrl(authState: any) {
    console.log("\n🔗 Generating authorization URL...");

    const params = new URLSearchParams({
        client_id: CLIENT_ID,
        redirect_uri: REDIRECT_URI,
        response_type: 'code',
        scope: 'openid profile email',
        code_challenge: authState.codeChallenge,
        code_challenge_method: 'S256',
        state: authState.state
    });

    const authUrl = `${DOMAIN}/oauth/v2/authorize?${params.toString()}`;
    console.log("✅ Authorization URL generated:");
    console.log(`   ${authUrl}`);

    return authUrl;
}

async function testTokenExchange(authorizationCode: string, codeVerifier: string) {
    console.log("\n🔄 Testing token exchange...");

    try {
        const tokens = await exchangeCodeForTokens(authorizationCode, codeVerifier);
        console.log("✅ Token exchange successful:");
        console.log(`   Access Token: ${tokens.access_token.substring(0, 20)}...`);
        console.log(`   ID Token: ${tokens.id_token.substring(0, 20)}...`);
        console.log(`   Token Type: ${tokens.token_type}`);
        console.log(`   Expires In: ${tokens.expires_in} seconds`);

        return tokens;
    } catch (error) {
        console.error("❌ Token exchange failed:", error);
        return null;
    }
}

async function testUserInfo(accessToken: string) {
    console.log("\n👤 Testing user info retrieval...");

    try {
        const userInfo = await getUserInfo(accessToken);
        console.log("✅ User info retrieved successfully:");
        console.log(`   User ID: ${userInfo.sub}`);
        console.log(`   Email: ${userInfo.email || 'N/A'}`);
        console.log(`   Name: ${userInfo.name || 'N/A'}`);
        console.log(`   Email Verified: ${userInfo.email_verified ? '✅' : '❌'}`);

        return userInfo;
    } catch (error) {
        console.error("❌ User info retrieval failed:", error);
        return null;
    }
}

function displayInstructions(authUrl: string) {
    console.log("\n📋 Manual Testing Instructions:");
    console.log("1. Open the following URL in your browser:");
    console.log(`   ${authUrl}`);
    console.log("\n2. Complete the authentication process");
    console.log("\n3. After redirect, copy the 'code' parameter from the callback URL");
    console.log("\n4. Run this script again with the authorization code:");
    console.log(`   bun run test-auth.ts <authorization_code>`);
}

async function main() {
    console.log("🚀 Zitadel PKCE Authentication Test\n");

    // Get authorization code from command line arguments
    const authorizationCode = process.argv[2];

    if (!authorizationCode) {
        // Generate PKCE parameters and show authorization URL
        const authState = await testPKCEGeneration();
        if (authState) {
            const authUrl = generateAuthorizationUrl(authState);
            displayInstructions(authUrl);

            // Save auth state for next run
            console.log("\n💾 Auth state saved for next test run:");
            console.log(`   Code Verifier: ${authState.codeVerifier}`);
        }
    } else {
        // Test token exchange with provided authorization code
        // Note: In real testing, you'd retrieve the stored code verifier
        console.log("⚠️  Please provide the code verifier used to generate the authorization URL");
        console.log("   This demo requires manual input for security reasons");
    }
}

// Run the test
main().catch(console.error);
