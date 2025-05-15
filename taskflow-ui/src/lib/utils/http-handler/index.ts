import { API_BASE_URL } from "$lib/api/config";
import axios from "axios";

type Options = {
    timeout: number
}

export class HttpHandler {

    static async PostCaller(name: string, data?: any, options: Options = { timeout: 10000 }): Promise<any> {
        try {
            const response = await axios.post(`${API_BASE_URL}/${name}`, data, { timeout: options.timeout });
            return this.validateResponse(response);
        } catch (error: any) {
            throw this.handleError(error);
        }
    }

    static async GetCaller(name: string, options: Options = { timeout: 10000 }): Promise<any> {
        try {
            const response = await axios.get(`${API_BASE_URL}/${name}`, { timeout: options.timeout });
            return this.validateResponse(response);
        } catch (error: any) {
            throw this.handleError(error);
        }
    }

    private static validateResponse(response: any): any {
        if (!response) {
            throw new Error('Response is null or undefined');
        }
        return response;
    }

    private static handleError(error: any): Error {
            if (error.response) {
                let status = error.response.status;
                switch (status) {
                    case 401:
                        return new Error('Unauthorized: Please log in.');
                    case 403:
                        return new Error('Forbidden: You do not have permission to access this resource.');
                    case 404:
                        return new Error('Not Found: The requested resource could not be found.');
                    case 500:
                        return new Error('Server Error: Please try again later.');
                    case 503:
                        return new Error('Service Unavailable: The server is currently unavailable.');
                    default:
                        return new Error(`API request failed with status ${status}: ${error.response.statusText}`);
                }
            } else if (error.request) {
                return new Error('No response from server. Please check your network connection.');
            }
        return new Error(`An unknown error occurred: ${error.message}`);
    }
}
