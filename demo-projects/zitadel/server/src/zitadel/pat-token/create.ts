import axios from 'axios';

export async function createPatToken(domain: string, token: string, userId: string): Promise<string> {
    try {
        const config = {
            method: 'post',
            maxBodyLength: Infinity,
            url: `https://${domain}/management/v1/users/${userId}/pats`,
            headers: {
                'Content-Type': 'application/json',
                'Accept': 'application/json',
                'Authorization': `Bearer ${token}`
            },
            data: {
                expirationDate: new Date(Date.now() + 1000 * 60 * 60 * 24 * 30).toISOString(), // 30 days from now
            }
        };

        const response = await axios.request(config);
        console.log("PAT Token created successfully:", response.status, response.data);
        return response.data.token;
    } catch (error) {
        console.error('Error creating PAT token:', error);
        return '';
    }
}