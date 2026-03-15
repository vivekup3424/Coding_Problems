import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

/**
 * Background service that polls tasks every minute and fires ReminderListener
 * callbacks when a reminder's due time has passed.
 *
 * Uses CopyOnWriteArrayList for listeners so addListener() is safe to call
 * from any thread without blocking the polling loop.
 */
public class ReminderService {
    private final TaskManager taskManager;
    private final List<ReminderListener> listeners = new CopyOnWriteArrayList<>();
    private final ScheduledExecutorService scheduler =
            Executors.newSingleThreadScheduledExecutor(r -> {
                Thread t = new Thread(r, "reminder-service");
                t.setDaemon(true);   // don't prevent JVM shutdown
                return t;
            });

    public ReminderService(TaskManager taskManager) {
        this.taskManager = taskManager;
    }

    public void addListener(ReminderListener listener) {
        listeners.add(listener);
    }

    /** Start polling every {@code intervalSeconds} seconds. */
    public void start(long intervalSeconds) {
        scheduler.scheduleAtFixedRate(this::checkReminders,
                0, intervalSeconds, TimeUnit.SECONDS);
    }

    public void stop() {
        scheduler.shutdown();
    }

    private void checkReminders() {
        for (Task task : taskManager.getAllTasks()) {
            for (Reminder reminder : task.getReminders()) {
                if (reminder.isDue()) {
                    reminder.markTriggered();
                    for (ReminderListener listener : listeners) {
                        try {
                            listener.onReminder(task, reminder);
                        } catch (Exception e) {
                            System.err.println("ReminderListener threw: " + e.getMessage());
                        }
                    }
                }
            }
        }
    }
}
