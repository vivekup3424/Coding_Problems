import axios, { type AxiosRequestConfig, type AxiosResponse } from "axios";
import fs from "fs";
import jwt from 'jsonwebtoken';
// Service User Credentials Interface
interface ServiceUserCredentials {
    keyId: string;
    key: string;
    clientId: string;
    userId?: string; // Optional for service accounts
}

export async function introspectPatToken(
    domain: string,
    patToken: string
): Promise<any> {
    let serviceUserCredentials: ServiceUserCredentials;
    let introspectionCredentials: ServiceUserCredentials;
    try {

        const apiKeyData = JSON.parse(fs.readFileSync('/Users/saitejaarava/Documents/playground/arena_2/zitadel/server/keys/api.json', 'utf8'));

        // Validate API credentials structure according to Zitadel documentation
        if (!apiKeyData.keyId || !apiKeyData.key || !apiKeyData.clientId) {
            throw new Error('Invalid API credentials format. Required: keyId, key, clientId');
        }

        introspectionCredentials = {
            keyId: apiKeyData.keyId,
            key: apiKeyData.key,
            clientId: apiKeyData.clientId
        };

        console.log('✅ Introspection credentials loaded successfully');
        console.log(`📋 Introspection Client ID: ${introspectionCredentials.clientId}`);
        console.log(`🔑 Introspection Key ID: ${introspectionCredentials.keyId}`);


        // Generate JWT client assertion for authentication
        const now = Math.floor(Date.now() / 1000);
        const clientAssertionJWT = jwt.sign({
            iss: introspectionCredentials.clientId,
            sub: introspectionCredentials.clientId,
            aud: `https://${domain}`, // Your ZITADEL domain/issuer URL
            exp: now + 3600, // Expires in 1 hour
            iat: now // Issued at time (MUST NOT be older than 1h)
        }, introspectionCredentials.key, {
            algorithm: 'RS256',
            keyid: introspectionCredentials.keyId
        });
        const config: AxiosRequestConfig = {
            method: 'post',
            url: `https://${domain}/oauth/v2/introspect`,
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded',
            },
            data: new URLSearchParams({
                token: patToken,
                client_assertion_type: 'urn:ietf:params:oauth:client-assertion-type:jwt-bearer',
                client_assertion: clientAssertionJWT
            })
        };

        console.log('🔍 Introspecting PAT token...' ,config);

        const response = await axios.request<unknown, AxiosResponse<any>>(config);

        // const response = await axios.post(`https://${domain}/oauth/v2/introspect`, new URLSearchParams({
        //     token: patToken, // The PAT token to introspect
        //     client_assertion_type: 'urn:ietf:params:oauth:client-assertion-type:jwt-bearer',
        //     client_assertion: clientAssertionJWT
        // }), {
        //     headers: {
        //         "Content-Type": "application/x-www-form-urlencoded",
        //     }
        // });
        console.log(JSON.stringify(response.data, null, 2));
        return response.data;
    } catch (error) {
        console.error("Error introspecting PAT token:", error);
        return false;
    }
}