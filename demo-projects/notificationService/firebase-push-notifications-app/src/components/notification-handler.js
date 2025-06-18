class NotificationHandler {
    constructor() {
        this.notificationPermission = Notification.permission;
    }

    requestPermission() {
        return Notification.requestPermission().then(permission => {
            this.notificationPermission = permission;
            return permission;
        });
    }

    showNotification(title, options) {
        if (this.notificationPermission === 'granted') {
            new Notification(title, options);
        }
    }

    handleNotificationClick(callback) {
        if (typeof callback === 'function') {
            window.addEventListener('notificationclick', (event) => {
                event.notification.close();
                callback(event);
            });
        }
    }
}

export default NotificationHandler;