import axios from 'axios';

export async function verifyOpt(domain: string, token: string, userId: string): Promise<any> {
    try {
        let data = JSON.stringify({
            "verificationCode": "SKJd342k"
        });

        let config = {
            method: 'post',
            maxBodyLength: Infinity,
            url: `https://${domain}/v2/users/${userId}/phone/verify`,
            headers: {
                'Content-Type': 'application/json',
                'Accept': 'application/json',
                'Authorization': `Bearer ${token}`
            },
            data: data
        };

        axios.request(config)
            .then((response) => {
                console.log(JSON.stringify(response.data));
            })
            .catch((error) => {
                console.log(error);
            });
    } catch (error) {
        console.error('Error verifying OPT:', error);
        return false;
    }
}