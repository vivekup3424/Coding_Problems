// Firebase Cloud Messaging Web App
import { initializeApp } from 'https://www.gstatic.com/firebasejs/10.7.1/firebase-app.js';
import { 
    getMessaging, 
    getToken, 
    onMessage,
    isSupported 
} from 'https://www.gstatic.com/firebasejs/10.7.1/firebase-messaging.js';
import { getAnalytics } from 'https://www.gstatic.com/firebasejs/10.7.1/firebase-analytics.js';

// Firebase configuration
const firebaseConfig = {
    apiKey: "AIzaSyDhKHTmOZDX-eBdHEMYF7xT_2IF-QO2ScU",
    authDomain: "earnest-vent-462706-n1.firebaseapp.com",
    projectId: "earnest-vent-462706-n1",
    storageBucket: "earnest-vent-462706-n1.firebasestorage.app",
    messagingSenderId: "683822082958",
    appId: "1:683822082958:web:dd77c955d0666dbb15d2df",
    measurementId: "G-DXBFB3ZWNC"
};

// VAPID key for web push
const vapidKey = "BHlQe0B2mQTDwdtnDa6s3-gXa7m0dd25RA3IX_YObWIpRMjn-WNUIJJomEr8kmEXYg3c9QQr5VGvGhFo9fq9eww"; // You'll need to generate this in Firebase Console

class FirebasePushNotificationApp {
    constructor() {
        this.app = null;
        this.messaging = null;
        this.analytics = null;
        this.fcmToken = null;
        this.notificationCount = 0;
        
        this.init();
    }

    async init() {
        try {
            // Initialize Firebase
            this.app = initializeApp(firebaseConfig);
            this.analytics = getAnalytics(this.app);
            
            // Check if messaging is supported
            const messagingSupported = await isSupported();
            if (!messagingSupported) {
                this.showError('Firebase Messaging is not supported in this browser');
                return;
            }
            
            this.messaging = getMessaging(this.app);
            
            // Set up UI event listeners
            this.setupEventListeners();
            
            // Check current permission status
            this.updatePermissionStatus();
            
            // Set up message listener
            this.setupMessageListener();
            
            console.log('Firebase app initialized successfully');
        } catch (error) {
            console.error('Error initializing Firebase:', error);
            this.showError('Failed to initialize Firebase: ' + error.message);
        }
    }

    setupEventListeners() {
        // Request permission button
        document.getElementById('request-permission').addEventListener('click', () => {
            this.requestNotificationPermission();
        });

        // Copy token button
        document.getElementById('copy-token').addEventListener('click', () => {
            this.copyTokenToClipboard();
        });

        // Send test notification button
        document.getElementById('send-test-notification').addEventListener('click', () => {
            this.sendTestNotification();
        });
    }

    updatePermissionStatus() {
        const permissionText = document.getElementById('permission-text');
        const requestButton = document.getElementById('request-permission');
        const permission = Notification.permission;

        permissionText.textContent = permission.charAt(0).toUpperCase() + permission.slice(1);
        
        // Add status indicator
        const indicator = document.createElement('span');
        indicator.className = `status-indicator status-${permission}`;
        permissionText.parentNode.insertBefore(indicator, permissionText);

        if (permission === 'granted') {
            requestButton.textContent = 'Notifications Enabled ✓';
            requestButton.disabled = true;
            this.getFCMToken();
        } else if (permission === 'denied') {
            requestButton.textContent = 'Notifications Blocked';
            requestButton.disabled = true;
            this.showError('Notifications are blocked. Please enable them in your browser settings.');
        } else {
            requestButton.textContent = 'Enable Notifications';
            requestButton.disabled = false;
        }
    }

    async requestNotificationPermission() {
        try {
            const permission = await Notification.requestPermission();
            
            if (permission === 'granted') {
                console.log('Notification permission granted');
                this.updatePermissionStatus();
                await this.getFCMToken();
            } else {
                console.log('Notification permission denied');
                this.updatePermissionStatus();
            }
        } catch (error) {
            console.error('Error requesting notification permission:', error);
            this.showError('Error requesting permission: ' + error.message);
        }
    }

    async getFCMToken() {
        try {
            // Register service worker first
            if ('serviceWorker' in navigator) {
                const registration = await navigator.serviceWorker.register('./firebase-messaging-sw.js');
                console.log('Service Worker registered:', registration);
            }

            const token = await getToken(this.messaging, { 
                vapidKey: vapidKey,
                serviceWorkerRegistration: await navigator.serviceWorker.ready
            });
            
            if (token) {
                this.fcmToken = token;
                console.log('FCM Token:', token);
                this.displayToken(token);
                this.enableTestNotification();
            } else {
                console.log('No registration token available');
                this.showError('Failed to get FCM token');
            }
        } catch (error) {
            console.error('Error getting FCM token:', error);
            this.showError('Error getting FCM token: ' + error.message);
        }
    }

    displayToken(token) {
        const tokenTextarea = document.getElementById('fcm-token');
        const copyButton = document.getElementById('copy-token');
        
        tokenTextarea.value = token;
        copyButton.disabled = false;
    }

    enableTestNotification() {
        const testButton = document.getElementById('send-test-notification');
        testButton.disabled = false;
    }

    async copyTokenToClipboard() {
        try {
            const tokenTextarea = document.getElementById('fcm-token');
            await navigator.clipboard.writeText(tokenTextarea.value);
            
            const copyButton = document.getElementById('copy-token');
            const originalText = copyButton.textContent;
            copyButton.textContent = 'Copied! ✓';
            copyButton.style.background = '#28a745';
            
            setTimeout(() => {
                copyButton.textContent = originalText;
                copyButton.style.background = '';
            }, 2000);
        } catch (error) {
            console.error('Error copying to clipboard:', error);
            this.showError('Failed to copy token to clipboard');
        }
    }

    setupMessageListener() {
        onMessage(this.messaging, (payload) => {
            console.log('Message received:', payload);
            this.handleIncomingMessage(payload);
        });
    }

    handleIncomingMessage(payload) {
        const { notification, data } = payload;
        
        // Log the notification
        this.logNotification({
            title: notification?.title || 'No title',
            body: notification?.body || 'No body',
            data: data || {},
            timestamp: new Date()
        });

        // Show browser notification if page is not focused
        if (document.hidden) {
            this.showBrowserNotification(notification);
        } else {
            // Show in-app notification
            this.showInAppNotification(notification);
        }
    }

    showBrowserNotification(notification) {
        if (Notification.permission === 'granted') {
            new Notification(notification.title, {
                body: notification.body,
                icon: notification.icon || '/icon-192x192.png',
                badge: '/icon-192x192.png',
                tag: 'firebase-notification',
                requireInteraction: true
            });
        }
    }

    showInAppNotification(notification) {
        // Create a temporary in-app notification
        const notificationEl = document.createElement('div');
        notificationEl.className = 'in-app-notification';
        notificationEl.innerHTML = `
            <div class="notification-content">
                <strong>${notification.title}</strong>
                <p>${notification.body}</p>
            </div>
            <button class="close-notification">&times;</button>
        `;
        
        // Add styles
        notificationEl.style.cssText = `
            position: fixed;
            top: 20px;
            right: 20px;
            background: white;
            border: 1px solid #ddd;
            border-radius: 8px;
            padding: 15px;
            box-shadow: 0 4px 20px rgba(0,0,0,0.15);
            z-index: 1000;
            max-width: 300px;
            animation: slideIn 0.3s ease;
        `;
        
        document.body.appendChild(notificationEl);
        
        // Auto remove after 5 seconds
        setTimeout(() => {
            if (notificationEl.parentNode) {
                notificationEl.remove();
            }
        }, 5000);
        
        // Close button
        notificationEl.querySelector('.close-notification').addEventListener('click', () => {
            notificationEl.remove();
        });
    }

    sendTestNotification() {
        const title = document.getElementById('notification-title').value || 'Test Notification';
        const body = document.getElementById('notification-body').value || 'This is a test message!';
        
        // Simulate receiving a message (for demo purposes)
        const simulatedPayload = {
            notification: {
                title: title,
                body: body,
                icon: '/icon-192x192.png'
            },
            data: {
                type: 'test',
                timestamp: Date.now().toString()
            }
        };
        
        this.handleIncomingMessage(simulatedPayload);
    }

    logNotification(notification) {
        const logContainer = document.getElementById('notifications-log');
        const emptyState = logContainer.querySelector('.empty-state');
        
        if (emptyState) {
            emptyState.remove();
        }
        
        const notificationEl = document.createElement('div');
        notificationEl.className = 'notification-item';
        notificationEl.innerHTML = `
            <div class="title">${notification.title}</div>
            <div class="body">${notification.body}</div>
            <div class="timestamp">${notification.timestamp.toLocaleString()}</div>
        `;
        
        logContainer.insertBefore(notificationEl, logContainer.firstChild);
        
        // Keep only last 10 notifications
        const notifications = logContainer.querySelectorAll('.notification-item');
        if (notifications.length > 10) {
            notifications[notifications.length - 1].remove();
        }
        
        this.notificationCount++;
    }

    showError(message) {
        console.error(message);
        
        // Create error notification
        const errorEl = document.createElement('div');
        errorEl.style.cssText = `
            position: fixed;
            top: 20px;
            left: 50%;
            transform: translateX(-50%);
            background: #dc3545;
            color: white;
            padding: 15px 20px;
            border-radius: 8px;
            box-shadow: 0 4px 20px rgba(0,0,0,0.15);
            z-index: 1001;
            max-width: 400px;
        `;
        errorEl.textContent = message;
        
        document.body.appendChild(errorEl);
        
        setTimeout(() => {
            if (errorEl.parentNode) {
                errorEl.remove();
            }
        }, 5000);
    }
}

// Initialize the app when DOM is loaded
document.addEventListener('DOMContentLoaded', () => {
    new FirebasePushNotificationApp();
});

// Add CSS animation for notifications
const style = document.createElement('style');
style.textContent = `
    @keyframes slideIn {
        from {
            opacity: 0;
            transform: translateX(100%);
        }
        to {
            opacity: 1;
            transform: translateX(0);
        }
    }
    
    .in-app-notification .notification-content {
        margin-bottom: 10px;
    }
    
    .close-notification {
        position: absolute;
        top: 5px;
        right: 10px;
        background: none;
        border: none;
        font-size: 20px;
        cursor: pointer;
        color: #666;
    }
`;
document.head.appendChild(style);