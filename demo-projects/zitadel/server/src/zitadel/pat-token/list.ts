import axios from 'axios';

export async function listAllPatTokens(domain: string, token: string, userId: string): Promise<string[]> {
    try {
        const config = {
            method: 'post',
            maxBodyLength: Infinity,
            url: `https://${domain}/management/v1/users/${userId}/pats/_search`,
            headers: {
                'Content-Type': 'application/json',
                'Accept': 'application/json',
                'Authorization': `Bearer ${token}`
            },
            data: {
                limit: 10000,
                asc: true,
            }
        };

        const response = await axios.request(config);
        console.log("PAT Token created successfully:", response.status, response.data);
        return response.data.result;
    } catch (error) {
        console.error('Error creating PAT token:', error);
        return [];
    }
}