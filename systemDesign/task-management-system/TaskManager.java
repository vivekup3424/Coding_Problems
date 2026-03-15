import java.time.LocalDateTime;
import java.util.Collection;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;
import java.util.stream.Collectors;

/**
 * Singleton facade for the task management system.
 *
 * Thread-safety strategy:
 *  - ConcurrentHashMap for the task/user stores (safe map operations).
 *  - Per-Task ReentrantReadWriteLock (inside Task) for field-level mutations.
 *  - Double-checked locking for singleton creation.
 */
public class TaskManager {

    // ── Singleton ─────────────────────────────────────────────────────────

    private static volatile TaskManager instance;

    private TaskManager() {}

    public static TaskManager getInstance() {
        if (instance == null) {
            synchronized (TaskManager.class) {
                if (instance == null) {
                    instance = new TaskManager();
                }
            }
        }
        return instance;
    }

    // ── State ──────────────────────────────────────────────────────────────

    private final ConcurrentHashMap<String, Task> tasks = new ConcurrentHashMap<>();
    private final ConcurrentHashMap<String, User> users = new ConcurrentHashMap<>();

    // ── User management ───────────────────────────────────────────────────

    public User registerUser(String name, String email) {
        User user = new User(name, email);
        users.put(user.getId(), user);
        return user;
    }

    public User getUser(String userId) {
        return getUserOrThrow(userId);
    }

    // ── Task CRUD ─────────────────────────────────────────────────────────

    public Task createTask(String creatorUserId, String title, String description,
                           LocalDateTime dueDate, TaskPriority priority) {
        getUserOrThrow(creatorUserId);   // validate creator exists
        Task task = new Task(title, description, dueDate, priority);
        tasks.put(task.getId(), task);
        return task;
    }

    /**
     * Partial update – pass null for any field you don't want to change.
     */
    public void updateTask(String userId, String taskId,
                           String title, String description,
                           LocalDateTime dueDate, TaskPriority priority) {
        Task task = getTaskOrThrow(taskId);
        if (title != null)       task.setTitle(userId, title);
        if (description != null) task.setDescription(userId, description);
        if (dueDate != null)     task.setDueDate(userId, dueDate);
        if (priority != null)    task.setPriority(userId, priority);
    }

    public void deleteTask(String taskId) {
        if (tasks.remove(taskId) == null) {
            throw new IllegalArgumentException("Task not found: " + taskId);
        }
    }

    public Task getTask(String taskId) {
        return getTaskOrThrow(taskId);
    }

    public Collection<Task> getAllTasks() {
        return tasks.values();
    }

    // ── Assignment ────────────────────────────────────────────────────────

    public void assignTask(String assignerUserId, String taskId, String assigneeUserId) {
        getUserOrThrow(assigneeUserId);   // validate assignee exists
        getTaskOrThrow(taskId).setAssignedUserId(assignerUserId, assigneeUserId);
    }

    // ── Status ────────────────────────────────────────────────────────────

    public void updateStatus(String userId, String taskId, TaskStatus status) {
        getTaskOrThrow(taskId).setStatus(userId, status);
    }

    public void markComplete(String userId, String taskId) {
        getTaskOrThrow(taskId).setStatus(userId, TaskStatus.COMPLETED);
    }

    // ── Reminders ─────────────────────────────────────────────────────────

    public void addReminder(String taskId, Reminder reminder) {
        getTaskOrThrow(taskId).addReminder(reminder);
    }

    // ── Search & Filter ───────────────────────────────────────────────────

    /**
     * Full-text search across title and description (case-insensitive).
     */
    public List<Task> searchTasks(String keyword) {
        String lower = keyword.toLowerCase();
        return tasks.values().stream()
                .filter(t -> t.getTitle().toLowerCase().contains(lower)
                          || t.getDescription().toLowerCase().contains(lower))
                .collect(Collectors.toList());
    }

    /**
     * Structured filtering via {@link TaskFilter} (builder pattern).
     */
    public List<Task> filterTasks(TaskFilter filter) {
        return tasks.values().stream()
                .filter(filter::matches)
                .collect(Collectors.toList());
    }

    // ── History ───────────────────────────────────────────────────────────

    public List<TaskHistoryEntry> getTaskHistory(String taskId) {
        return getTaskOrThrow(taskId).getHistory();
    }

    // ── Helpers ───────────────────────────────────────────────────────────

    private Task getTaskOrThrow(String taskId) {
        Task task = tasks.get(taskId);
        if (task == null) throw new IllegalArgumentException("Task not found: " + taskId);
        return task;
    }

    private User getUserOrThrow(String userId) {
        User user = users.get(userId);
        if (user == null) throw new IllegalArgumentException("User not found: " + userId);
        return user;
    }
}
