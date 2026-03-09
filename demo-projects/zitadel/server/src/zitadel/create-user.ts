import axios from "axios";
import * as uuid from "uuid"
import fs from "fs/promises"

export async function createUser(
    domain: string,
    token: string,
): Promise<any> {
    try {
        const userid = uuid.v4();
        let data = JSON.stringify({
            "userId": userid,
            "username": "sai-test-user-1",
            "organization": {
                "orgId": "332277518549647366",
                // "orgDomain": "string"
            },
            "profile": {
                "givenName": "zitadel-test-sai-1",
                "familyName": "Keus",
                // "nickName": "Mini",
                // "displayName": "Minnie Mouse",
                // "preferredLanguage": "en",
                // "gender": "GENDER_FEMALE"
            },
            "email": {
                "email": "aravasaitejaenduser@gmail.com",
                // "sendCode": {
                //     "urlTemplate": "https://example.com/email/verify?userID={{.UserID}}&code={{.Code}}&orgID={{.OrgID}}"
                // },
                // "returnCode": {},
                "isVerified": true
            },
            "phone": {
                "phone": "+91 7569929617",
                // "sendCode": {},
                // "returnCode": {},
                "isVerified": true
            },
            // "metadata": [
            //     {
            //         "key": "my-key",
            //         "value": "VGhpcyBpcyBteSB0ZXN0IHZhbHVl"
            //     }
            // ],
            "password": {
                "password": "Secr3tP4ssw0rd!",
                "changeRequired": false
            },
            // "hashedPassword": {
            //     "hash": "$2a$12$lJ08fqVr8bFJilRVnDT9QeULI7YW.nT3iwUv6dyg0aCrfm3UY8XR2",
            //     "changeRequired": true
            // },
            // "idpLinks": [
            //     {
            //         "idpId": "d654e6ba-70a3-48ef-a95d-37c8d8a7901a",
            //         "userId": "6516849804890468048461403518",
            //         "userName": "user@external.com"
            //     }
            // ],
            // "totpSecret": "TJOPWSDYILLHXFV4MLKNNJOWFG7VSDCK"
        });

        let config = {
            method: 'post',
            maxBodyLength: Infinity,
            url: `https://${domain}/v2/users/human`,
            headers: {
                'Content-Type': 'application/json',
                'Accept': 'application/json',
                'Authorization': `Bearer ${token}`
            },
            data: data
        };

        const response = await axios.request(config)
        console.log("User created successfully:",JSON.stringify(response.data));

        fs.appendFile("user-create.json", `"${userid}"` + "\n")
        
        console.log("----------Created user----------",response.status);
    } catch (error) {
        console.error("Error creating user:", error);
        console.log("----------Error creating user----------");
        return false;
    }
}