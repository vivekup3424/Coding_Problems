/**
 * Observer interface for reminder notifications.
 * Register implementations with ReminderService to receive alerts.
 */
@FunctionalInterface
public interface ReminderListener {
    void onReminder(Task task, Reminder reminder);
}
