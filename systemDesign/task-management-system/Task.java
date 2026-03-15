import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.UUID;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * Thread-safe Task entity. All mutations are recorded in history.
 * Uses a per-task ReadWriteLock for fine-grained concurrency control.
 */
public class Task {
    private final String id;
    private String title;
    private String description;
    private LocalDateTime dueDate;
    private TaskPriority priority;
    private TaskStatus status;
    private String assignedUserId;
    private final List<Reminder> reminders;
    private final List<TaskHistoryEntry> history;
    private final LocalDateTime createdAt;
    private LocalDateTime updatedAt;

    private final ReentrantReadWriteLock lock = new ReentrantReadWriteLock();

    public Task(String title, String description, LocalDateTime dueDate, TaskPriority priority) {
        this.id = UUID.randomUUID().toString();
        this.title = title;
        this.description = description;
        this.dueDate = dueDate;
        this.priority = priority;
        this.status = TaskStatus.PENDING;
        this.reminders = new ArrayList<>();
        this.history = new ArrayList<>();
        this.createdAt = LocalDateTime.now();
        this.updatedAt = LocalDateTime.now();
    }

    // ── Getters (read lock) ────────────────────────────────────────────────

    public String getId() {
        lock.readLock().lock();
        try { return id; } finally { lock.readLock().unlock(); }
    }

    public String getTitle() {
        lock.readLock().lock();
        try { return title; } finally { lock.readLock().unlock(); }
    }

    public String getDescription() {
        lock.readLock().lock();
        try { return description; } finally { lock.readLock().unlock(); }
    }

    public LocalDateTime getDueDate() {
        lock.readLock().lock();
        try { return dueDate; } finally { lock.readLock().unlock(); }
    }

    public TaskPriority getPriority() {
        lock.readLock().lock();
        try { return priority; } finally { lock.readLock().unlock(); }
    }

    public TaskStatus getStatus() {
        lock.readLock().lock();
        try { return status; } finally { lock.readLock().unlock(); }
    }

    public String getAssignedUserId() {
        lock.readLock().lock();
        try { return assignedUserId; } finally { lock.readLock().unlock(); }
    }

    public LocalDateTime getCreatedAt() {
        lock.readLock().lock();
        try { return createdAt; } finally { lock.readLock().unlock(); }
    }

    public LocalDateTime getUpdatedAt() {
        lock.readLock().lock();
        try { return updatedAt; } finally { lock.readLock().unlock(); }
    }

    /** Returns a snapshot of the history list. */
    public List<TaskHistoryEntry> getHistory() {
        lock.readLock().lock();
        try { return Collections.unmodifiableList(new ArrayList<>(history)); }
        finally { lock.readLock().unlock(); }
    }

    /** Returns a snapshot of the reminders list. */
    public List<Reminder> getReminders() {
        lock.readLock().lock();
        try { return Collections.unmodifiableList(new ArrayList<>(reminders)); }
        finally { lock.readLock().unlock(); }
    }

    // ── Setters (write lock, history recorded) ────────────────────────────

    public void setTitle(String userId, String title) {
        lock.writeLock().lock();
        try {
            history.add(new TaskHistoryEntry(userId, "title", this.title, title));
            this.title = title;
            this.updatedAt = LocalDateTime.now();
        } finally { lock.writeLock().unlock(); }
    }

    public void setDescription(String userId, String description) {
        lock.writeLock().lock();
        try {
            history.add(new TaskHistoryEntry(userId, "description", this.description, description));
            this.description = description;
            this.updatedAt = LocalDateTime.now();
        } finally { lock.writeLock().unlock(); }
    }

    public void setDueDate(String userId, LocalDateTime dueDate) {
        lock.writeLock().lock();
        try {
            history.add(new TaskHistoryEntry(userId, "dueDate",
                    String.valueOf(this.dueDate), String.valueOf(dueDate)));
            this.dueDate = dueDate;
            this.updatedAt = LocalDateTime.now();
        } finally { lock.writeLock().unlock(); }
    }

    public void setPriority(String userId, TaskPriority priority) {
        lock.writeLock().lock();
        try {
            history.add(new TaskHistoryEntry(userId, "priority",
                    String.valueOf(this.priority), String.valueOf(priority)));
            this.priority = priority;
            this.updatedAt = LocalDateTime.now();
        } finally { lock.writeLock().unlock(); }
    }

    public void setStatus(String userId, TaskStatus status) {
        lock.writeLock().lock();
        try {
            history.add(new TaskHistoryEntry(userId, "status",
                    String.valueOf(this.status), String.valueOf(status)));
            this.status = status;
            this.updatedAt = LocalDateTime.now();
        } finally { lock.writeLock().unlock(); }
    }

    public void setAssignedUserId(String assignerUserId, String assigneeUserId) {
        lock.writeLock().lock();
        try {
            history.add(new TaskHistoryEntry(assignerUserId, "assignedUserId",
                    this.assignedUserId, assigneeUserId));
            this.assignedUserId = assigneeUserId;
            this.updatedAt = LocalDateTime.now();
        } finally { lock.writeLock().unlock(); }
    }

    public void addReminder(Reminder reminder) {
        lock.writeLock().lock();
        try { reminders.add(reminder); }
        finally { lock.writeLock().unlock(); }
    }

    @Override
    public String toString() {
        lock.readLock().lock();
        try {
            return String.format("Task{id='%s', title='%s', priority=%s, status=%s, dueDate=%s, assignedTo=%s}",
                    id.substring(0, 8), title, priority, status, dueDate, assignedUserId);
        } finally { lock.readLock().unlock(); }
    }
}
