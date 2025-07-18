interface User {
    id: string;
    identifier: string; // Unique identifier for the user(for clevertap purpose)
    name: string;
    email: string;
    phoneNumber: string;
    deviceId: string[]; // For push notifications
    siteId: string; // unique identifier for the home
    gatewayId: string; //unque identifier for the hub inside home
}
export type {
    User
}