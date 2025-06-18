class SubscriptionManager {
    constructor(messaging) {
        this.messaging = messaging;
    }

    async requestPermission() {
        try {
            await this.messaging.requestPermission();
            console.log("Notification permission granted.");
            return true;
        } catch (error) {
            console.error("Unable to get permission to notify.", error);
            return false;
        }
    }

    async subscribeToTopic(topic) {
        try {
            const token = await this.messaging.getToken();
            if (token) {
                // Here you would typically send the token to your server to subscribe to the topic
                console.log(`Subscribed to topic: ${topic} with token: ${token}`);
            } else {
                console.log("No registration token available. Request permission to generate one.");
            }
        } catch (error) {
            console.error("Error subscribing to topic:", error);
        }
    }
}

export default SubscriptionManager;