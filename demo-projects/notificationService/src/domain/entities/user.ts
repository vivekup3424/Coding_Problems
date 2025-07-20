class User {
    id: string;
    identifier: string; // Unique identifier for the user(for clevertap purpose)
    name: string;
    email: string;
    phoneNumber: string;
    deviceId: string[]; // For push notifications
    siteId: string; // unique identifier for the home
    gatewayId: string; //unque identifier for the hub inside home
    constructor(id: string, identifier: string, name: string, email: string, phoneNumber: string, deviceId: string[], siteId: string, gatewayId: string) {
        this.id = id;
        this.identifier = identifier;
        this.name = name;
        this.email = email;
        this.phoneNumber = phoneNumber;
        this.deviceId = deviceId;
        this.siteId = siteId;
        this.gatewayId = gatewayId;
    }
}
export type {
    User
}