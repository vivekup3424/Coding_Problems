## Classification of Notifications
### Based on criticality level
1. High
    - Retry the nofication until delivery
    - Immediate delivery of notification
    - In the message of notification, add a callback function to prompt the user to do after step correction
2. Medium
    - Fixed retry count, then return the error
    - Immediate delivery of nofitication
3. Low
    - No retries (fireNforget)

### Notification Types
1. SMS Provider
    - We would be using a custom provider for this
    - it would take an access token
    - an number
2. Push-Notification Provider
    - We would be using Firebase Cloud messaging
    - So we need to have whatever required fields are required
3. Email Provider
    - Some utility like send grid

Functional Requirements
1. Should be able create subscriber at runtime and populate them with fields like
    - their firstname, lastname, phone number, email-id
2. Group multiple subscribers under one topic
3. Notifications' lifecyle need to be tracks, like are they in sent or not,
    have they been acknowledged by the receiver
4. Particularly for highly critical notification we need some ackowledgment confirmation from subscriber
5. Suppose our notification server sents a notification to subscriber A, during after creating the notification suppose the notification server went offline so it didn't got the ackowledgment that subscriber has got the notification, but in reality the subscriber has got the notification
How we I manage idempotency of notification so that they don't get repeated
Surely for every notification I can create a hashkey and store it inside a bloom-filter so that....

6. Should be able to send notification on a topic or to a particular subscriber
7. Should be create a basic template for notification at runtime which can be used for sending notification
to difference subscriber
8. Store the list of notification on the notification server, side so that when the notification is to be send again
We are creating it from scratch
Need to make use of moleculer-action for retry mechanism
For forgetNfire situation I can create events, which are being listened by notification service

Make use of design patterns and clean code architecture