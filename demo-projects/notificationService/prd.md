Notifications Infrastructure PRD
Overview
This project supports the business logic team by providing tools necessary to implement a robust notifications system into the primary application.
Feature Specifications
1. Local Inboxes for Notifications
Developers can create multiple local inboxes for storing notifications with the following capabilities:
Store push notifications to an inbox
Maintain and track read/unread status.
Pagination support for efficient retrieval.
Ability to delete notifications.
Edge Cases and Solutions:
Inbox Overflow: Implement automatic deletion or archiving rules when inboxes reach capacity, with warnings provided to developers.
2. Flexible Push Notification Targeting
Provide flexibility for sending notifications to:
All devices of a user.
Specific devices.
Users within designated groups (use case for sending to all users and devices of the home).
Edge Cases and Solutions:
Device Changes: Periodically verify registered devices and update target mappings.
Group Modifications: Dynamically manage notification distribution lists upon group membership changes.


3. Validity and Buffering of Notifications
Buffer notifications during connectivity loss.
Send buffered notifications upon connectivity restoration.
Assign validity periods to notifications to ensure timely delivery.
Edge Cases and Solutions:
Buffer Overflow: Limit the buffer size and prioritize notifications based on importance or recency.
Expired Notifications: Regularly clean the buffer by discarding expired notifications, logging these instances.
4. Managing Read and Unread Status
Enable developers to track and manage notifications clearly:
Methods for marking notifications as read/unread.
Visual indicators in notification centers.
Edge Cases and Solutions:
Synchronization Across Devices: Implement cloud-based syncing for status changes to ensure consistency across devices.
State Conflicts: Apply timestamp-based conflict resolution.
5. Fallback Notification Channel
Automatically trigger fallback notifications (Whatsapp, SMS, Automated phone calls) if the original notification is not read within a predefined timeframe ( 5 min ).
Edge Cases and Solutions:
Fallback Failures: Provide alternative fallback mechanisms (e.g., email) and logging for failed deliveries.
Multiple Delivery Attempts: Set a limit on retries to prevent spam or user annoyance.
6. Multi-Channel Notification Support
Enable notifications to be delivered through multiple communication channels, including:
Push notifications
SMS
WhatsApp messages
Automated phone calls (voice notifications)
Edge Cases and Solutions:
Channel Availability Issues:
 Implement a prioritization mechanism for fallback channels, ensuring delivery even if the preferred channel fails.
User Channel Preferences:
 Allow users to set and manage preferred notification channels to avoid redundancy or user annoyance.
