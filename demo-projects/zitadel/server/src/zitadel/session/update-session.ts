import axios from 'axios';
import fs from 'fs/promises'

export async function updateSession(domain: string, token: string, sessionId: string, otp: string): Promise<any> {
    try {
        let data = JSON.stringify({
            "checks": {
                // "user": {
                //     "userId": userId,
                //     // "loginName": "owner"
                // },
                // "password": {
                //     "password": "V3ryS3cure!"
                // },
                // "webAuthN": {
                //     "credentialAssertionData": {}
                // },
                // "idpIntent": {
                //     "idpIntentId": "d654e6ba-70a3-48ef-a95d-37c8d8a7901a",
                //     "idpIntentToken": "SJKL3ioIDpo342ioqw98fjp3sdf32wahb="
                // },
                // "totp": {
                //     "code": "323764"
                // },
                "otpSms": {
                    "code": otp
                },
                // "otpEmail": {
                //     "code": "3237642"
                // }
            },
            // "metadata": {},
            // "challenges": {
            //     // "webAuthN": {
            //     //     "domain": "string",
            //     //     "userVerificationRequirement": "USER_VERIFICATION_REQUIREMENT_UNSPECIFIED"
            //     // },
            //     // "otpSms": {
            //     //     "returnCode": true
            //     // },
            //     // "otpEmail": {
            //     //     "sendCode": {
            //     //         "urlTemplate": "https://example.com/otp/verify?userID={{.UserID}}&code={{.Code}}"
            //     //     },
            //     //     "returnCode": {}
            //     // }
            // },
            // "userAgent": {
            //     "fingerprintId": "string",
            //     "ip": "string",
            //     "description": "string",
            //     "header": {}
            // },
            "lifetime": "18000s"
        });

        let config = {
            method: 'patch',
            maxBodyLength: Infinity,
            url: `https://${domain}/v2/sessions/${sessionId}`,
            headers: {
                'Content-Type': 'application/json',
                'Accept': 'application/json',
                'Authorization': `Bearer ${token}`
            },
            data: data
        };

        const response = await axios.request(config)
        console.log(JSON.stringify(response.data, null, 2));
        fs.writeFile("session-create.json", JSON.stringify(response.data, null, 2) + "\n");
        console.log("----------updated session----------", response.status);
    } catch (error) {
        console.error('Error creating session:', error);
        return false;
    }
}