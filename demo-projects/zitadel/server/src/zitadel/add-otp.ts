import axios from "axios";
export async function addOtp(domain: string, token: string, userId: string): Promise<any> {
    try {
        let data = JSON.stringify({});

        let config = {
            method: 'post',
            maxBodyLength: Infinity,
            url: `https://${domain}/v2/users/${userId}/otp_sms`,
            headers: {
                'Content-Type': 'application/json',
                'Accept': 'application/json',
                'Authorization': `Bearer ${token}`
            },
            data: data
        };

        const response = await axios.request(config)
        console.log(JSON.stringify(response.data));

    } catch (error) {
        console.error('Error adding OTP:', error);
        return false;
    }
}