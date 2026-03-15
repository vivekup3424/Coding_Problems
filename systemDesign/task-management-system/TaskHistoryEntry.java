import java.time.LocalDateTime;

public class TaskHistoryEntry {
    private final LocalDateTime timestamp;
    private final String userId;
    private final String field;
    private final String oldValue;
    private final String newValue;

    public TaskHistoryEntry(String userId, String field, String oldValue, String newValue) {
        this.timestamp = LocalDateTime.now();
        this.userId = userId;
        this.field = field;
        this.oldValue = oldValue;
        this.newValue = newValue;
    }

    public LocalDateTime getTimestamp() { return timestamp; }
    public String getUserId()           { return userId; }
    public String getField()            { return field; }
    public String getOldValue()         { return oldValue; }
    public String getNewValue()         { return newValue; }

    @Override
    public String toString() {
        return String.format("[%s] user=%s  %s: '%s' -> '%s'", timestamp, userId, field, oldValue, newValue);
    }
}
