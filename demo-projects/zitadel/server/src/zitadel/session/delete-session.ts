import axios from 'axios';
import fs from 'fs/promises'

export async function deleteSession(domain: string, token: string, sessionId: string): Promise<any> {
    try {

        let config = {
            method: 'delete',
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
        fs.truncate("session-create.json");
        console.log("----------Deleted session----------",response.status);
    } catch (error) {
        console.error('Error creating session:', error);
        return false;
    }
}