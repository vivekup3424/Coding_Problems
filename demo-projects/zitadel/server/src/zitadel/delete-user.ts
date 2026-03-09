import axios from 'axios';
import fs from 'fs/promises';

export async function deleteUser(domain: string, token: string, userId: string): Promise<any> {
    try {
        let config = {
            method: 'delete',
            maxBodyLength: Infinity,
            url: `https://${domain}/v2/users/${userId}`,
            headers: {
                'Accept': 'application/json',
                'Authorization': `Bearer ${token}`
            }
        };

        const response = await axios.request(config);
        fs.truncate("user-create.json");
        console.log("User deleted successfully:", JSON.stringify(response.data), response.status);
    } catch (error) {
        console.error('Error deleting user:', error);
        return false;
    }
}
