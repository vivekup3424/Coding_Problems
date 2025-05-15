export declare const load: ({ params, fetch }: {
    params: any;
    fetch: any;
}) => Promise<{
    taskflow: any;
    status?: undefined;
    error?: undefined;
} | {
    status: number;
    error: Error;
    taskflow?: undefined;
}>;
