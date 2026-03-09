import axios from 'axios';

export async function getUser(domain: string, token: string, userId: string): Promise<any> {
    try {

        let config = {
            method: 'get',
            maxBodyLength: Infinity,
            url: `https://${domain}/v2/users/${userId}`,
            headers: {
                'Accept': 'application/json',
                'Authorization': `Bearer ${token}`
            }
        };

        axios.request(config)
            .then((response:any) => {
                console.log(JSON.stringify(response.data, null, 2));
                console.log(response.status)
            })
            .catch((error:any) => {
                console.log(error);
            });
    } catch (error) {
        console.error('Error verifying OPT:', error);
        return false;
    }
}