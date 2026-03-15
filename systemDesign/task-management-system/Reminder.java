import java.time.LocalDateTime;
import java.util.UUID;

public class Reminder {
    private final String id;
    private final LocalDateTime reminderTime;
    private final String message;
    private volatile boolean triggered;

    public Reminder(LocalDateTime reminderTime, String message) {
        this.id = UUID.randomUUID().toString();
        this.reminderTime = reminderTime;
        this.message = message;
        this.triggered = false;
    }

    public String getId()                  { return id; }
    public LocalDateTime getReminderTime() { return reminderTime; }
    public String getMessage()             { return message; }
    public boolean isTriggered()           { return triggered; }

    public boolean isDue() {
        return !triggered && LocalDateTime.now().isAfter(reminderTime);
    }

    public void markTriggered() {
        this.triggered = true;
    }

    @Override
    public String toString() {
        return String.format("Reminder{time=%s, message='%s', triggered=%s}", reminderTime, message, triggered);
    }
}
