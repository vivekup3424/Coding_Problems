import axios from "axios";

export async function deletePatToken(domain: string, userId: string, token: string, patId: string): Promise<any> {
    try {
        let config = {
            method: 'delete',
            maxBodyLength: Infinity,
            url: `https://${domain}/management/v1/users/${userId}/pats/${patId}`,
            headers: {
                'Content-Type': 'application/json',
                'Accept': 'application/json',
                'Authorization': `Bearer ${token}`
            },
        };

        const response = await axios.request(config);
        console.log(JSON.stringify(response.data, null, 2));
        console.log("----------Deleted PAT Token----------", response.status, response.data);
    } catch (error) {
        console.error('Error deleting PAT Token:', error);
        return false;
    }
}