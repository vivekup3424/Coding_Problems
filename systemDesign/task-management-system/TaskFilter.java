import java.time.LocalDateTime;

/**
 * Immutable filter criteria built with a fluent Builder.
 * Call filter.matches(task) to test a task against all set criteria.
 */
public class TaskFilter {
    private final TaskPriority priority;
    private final TaskStatus status;
    private final String assignedUserId;
    private final LocalDateTime dueBefore;
    private final LocalDateTime dueAfter;
    private final String titleContains;

    private TaskFilter(Builder b) {
        this.priority       = b.priority;
        this.status         = b.status;
        this.assignedUserId = b.assignedUserId;
        this.dueBefore      = b.dueBefore;
        this.dueAfter       = b.dueAfter;
        this.titleContains  = b.titleContains;
    }

    public boolean matches(Task task) {
        if (priority != null && task.getPriority() != priority)
            return false;
        if (status != null && task.getStatus() != status)
            return false;
        if (assignedUserId != null && !assignedUserId.equals(task.getAssignedUserId()))
            return false;
        if (dueBefore != null && task.getDueDate() != null && task.getDueDate().isAfter(dueBefore))
            return false;
        if (dueAfter != null && task.getDueDate() != null && task.getDueDate().isBefore(dueAfter))
            return false;
        if (titleContains != null && !task.getTitle().toLowerCase().contains(titleContains.toLowerCase()))
            return false;
        return true;
    }

    public static class Builder {
        private TaskPriority priority;
        private TaskStatus status;
        private String assignedUserId;
        private LocalDateTime dueBefore;
        private LocalDateTime dueAfter;
        private String titleContains;

        public Builder priority(TaskPriority priority)          { this.priority = priority;             return this; }
        public Builder status(TaskStatus status)                { this.status = status;                 return this; }
        public Builder assignedUserId(String assignedUserId)    { this.assignedUserId = assignedUserId; return this; }
        public Builder dueBefore(LocalDateTime dueBefore)       { this.dueBefore = dueBefore;           return this; }
        public Builder dueAfter(LocalDateTime dueAfter)         { this.dueAfter = dueAfter;             return this; }
        public Builder titleContains(String titleContains)      { this.titleContains = titleContains;   return this; }

        public TaskFilter build() { return new TaskFilter(this); }
    }
}
