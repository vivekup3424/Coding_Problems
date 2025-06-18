// Firebase Messaging Service Worker
importScripts('https://www.gstatic.com/firebasejs/10.7.1/firebase-app-compat.js');
importScripts('https://www.gstatic.com/firebasejs/10.7.1/firebase-messaging-compat.js');

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

// Initialize Firebase
firebase.initializeApp(firebaseConfig);

// Initialize Firebase Cloud Messaging and get a reference to the service
const messaging = firebase.messaging();

// Handle background messages
messaging.onBackgroundMessage((payload) => {
    console.log('Received background message: ', payload);
    
    const notificationTitle = payload.notification?.title || 'Firebase Notification';
    const notificationOptions = {
        body: payload.notification?.body || 'You have a new message',
        icon: payload.notification?.icon || '/icon-192x192.png',
        badge: '/icon-192x192.png',
        tag: 'firebase-notification',
        data: {
            url: payload.data?.url || '/',
            ...payload.data
        },
        actions: [
            {
                action: 'open',
                title: 'Open App',
                icon: '/icon-192x192.png'
            },
            {
                action: 'close',
                title: 'Close',
                icon: '/icon-192x192.png'
            }
        ],
        requireInteraction: true,
        silent: false
    };

    return self.registration.showNotification(notificationTitle, notificationOptions);
});

// Handle notification click events
self.addEventListener('notificationclick', (event) => {
    console.log('Notification clicked:', event);
    
    event.notification.close();
    
    if (event.action === 'close') {
        return;
    }
    
    const urlToOpen = event.notification.data?.url || '/';
    
    event.waitUntil(
        clients.matchAll({
            type: 'window',
            includeUncontrolled: true
        }).then((clientList) => {
            // Check if there's already a window/tab open with the target URL
            for (const client of clientList) {
                if (client.url === urlToOpen && 'focus' in client) {
                    return client.focus();
                }
            }
            
            // If no window/tab is open, open a new one
            if (clients.openWindow) {
                return clients.openWindow(urlToOpen);
            }
        })
    );
});

// Handle notification close events
self.addEventListener('notificationclose', (event) => {
    console.log('Notification closed:', event);
    
    // Optional: Send analytics or tracking data
    // You can add your own logic here
});

// Handle push events (for custom payload processing)
self.addEventListener('push', (event) => {
    console.log('Push event received:', event);
    
    if (event.data) {
        const data = event.data.json();
        console.log('Push data:', data);
        
        // Custom handling for different types of notifications
        if (data.type === 'custom') {
            const notificationTitle = data.title || 'Custom Notification';
            const notificationOptions = {
                body: data.body || 'Custom notification body',
                icon: data.icon || '/icon-192x192.png',
                badge: '/icon-192x192.png',
                tag: data.tag || 'custom-notification',
                data: data.data || {},
                requireInteraction: data.requireInteraction || false
            };
            
            event.waitUntil(
                self.registration.showNotification(notificationTitle, notificationOptions)
            );
        }
    }
});

// Service Worker installation
self.addEventListener('install', (event) => {
    console.log('Service Worker installing');
    self.skipWaiting();
});

// Service Worker activation
self.addEventListener('activate', (event) => {
    console.log('Service Worker activating');
    event.waitUntil(self.clients.claim());
});