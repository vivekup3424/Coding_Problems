import type { IInboxRepository, InboxOperationResult } from "@domain/repositories/inbox-repo-interface";
import { NotificationStatus, type Notification } from "@domain/entities/notification";
import type { INotificationRepository } from "@domain/repositories/notification-repo-interface";

export class AddNotificationToInboxUsecase {
    private notificationRepository: INotificationRepository;
    constructor(inboxRepository: IInboxRepository, notificationRepository: INotificationRepository) {
        this.notificationRepository = notificationRepository;
    }

    async execute(inboxId: string, notificationId: string): Promise<InboxOperationResult> {
        try {
            const result = await this.notificationRepository.updateNotification(notificationId, {
                inboxId: inboxId,
                status: NotificationStatus.SENT
            });
            if (!result) {
                return { success: false, error: "Notification not found or not updated" };
            }
            return { success: true, data: "notification added in inbox" };
        } catch (err) {
            // @ts-ignore
            return { success: false, error: err.toString() };
        }
    }
}
