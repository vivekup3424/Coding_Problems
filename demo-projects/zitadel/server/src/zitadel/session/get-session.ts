import axios from 'axios';
import fs from 'fs/promises'

export async function getSession(domain: string, token: string, sessionId: string): Promise<any> {
    try {

        let config = {
            method: 'get',
            maxBodyLength: Infinity,
            url: `https://${domain}/v2/sessions/${sessionId}`,
            headers: {
                'Content-Type': 'application/json',
                'Accept': 'application/json',
                'Authorization': `Bearer ${token}`
            },
        };

        const response = await axios.request(config)
        console.log(JSON.stringify(response.data, null, 2));
        fs.writeFile("session-create.json",JSON.stringify(response.data, null, 2) + "\n");
        console.log("----------get session----------", response.status);
    } catch (error) {
        console.error('Error creating session:', error);
        return false;
    }
}