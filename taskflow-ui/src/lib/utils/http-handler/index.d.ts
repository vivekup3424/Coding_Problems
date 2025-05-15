type Options = {
    timeout: number;
};
export declare class HttpHandler {
    static PostCaller(name: string, data?: any, options?: Options): Promise<any>;
    static GetCaller(name: string, options?: Options): Promise<any>;
    private static validateResponse;
    private static handleError;
}
export {};
