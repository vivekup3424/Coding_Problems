import java.time.LocalDateTime;
import java.util.List;

/**
 * Demo driver for the Task Management System.
 *
 * Compile:  javac *.java
 * Run:      java Main
 */
public class Main {

    public static void main(String[] args) throws InterruptedException {

        TaskManager tm = TaskManager.getInstance();

        // ── Register users ────────────────────────────────────────────────
        User alice = tm.registerUser("Alice", "alice@example.com");
        User bob   = tm.registerUser("Bob",   "bob@example.com");
        System.out.println("Registered: " + alice);
        System.out.println("Registered: " + bob);

        // ── Create tasks ──────────────────────────────────────────────────
        Task t1 = tm.createTask(alice.getId(),
                "Design DB schema",
                "Design the database schema for the new feature",
                LocalDateTime.now().plusDays(3), TaskPriority.HIGH);

        Task t2 = tm.createTask(alice.getId(),
                "Write unit tests",
                "Write unit tests for the auth module",
                LocalDateTime.now().plusDays(7), TaskPriority.MEDIUM);

        Task t3 = tm.createTask(bob.getId(),
                "Fix login bug",
                "Fix the bug causing login failures on mobile devices",
                LocalDateTime.now().plusDays(1), TaskPriority.HIGH);

        System.out.println("\n=== Created Tasks ===");
        print(t1); print(t2); print(t3);

        // ── Assign t1 to Bob ──────────────────────────────────────────────
        tm.assignTask(alice.getId(), t1.getId(), bob.getId());
        System.out.println("\n=== After assigning t1 to Bob ===");
        System.out.println("t1 assignedUserId: " + t1.getAssignedUserId());

        // ── Partial update t2 ─────────────────────────────────────────────
        tm.updateTask(alice.getId(), t2.getId(),
                "Write unit tests (updated)", null, null, TaskPriority.HIGH);
        System.out.println("\n=== After updating t2 ===");
        print(t2);

        // ── Change status ─────────────────────────────────────────────────
        tm.updateStatus(bob.getId(), t3.getId(), TaskStatus.IN_PROGRESS);

        // ── Add reminder (fires in 2 s for demo) ──────────────────────────
        tm.addReminder(t3.getId(),
                new Reminder(LocalDateTime.now().plusSeconds(2), "Login bug due soon!"));

        // ── Start reminder service (poll every 1 s for demo) ──────────────
        ReminderService reminderService = new ReminderService(tm);
        reminderService.addListener((task, reminder) ->
                System.out.printf("%n[REMINDER] \"%s\" → %s%n", task.getTitle(), reminder.getMessage()));
        reminderService.start(1);

        // ── Filter: HIGH priority ─────────────────────────────────────────
        System.out.println("\n=== HIGH priority tasks ===");
        List<Task> highPri = tm.filterTasks(new TaskFilter.Builder()
                .priority(TaskPriority.HIGH).build());
        highPri.forEach(Main::print);

        // ── Filter: due within next 2 days ────────────────────────────────
        System.out.println("\n=== Due within 2 days ===");
        List<Task> dueSoon = tm.filterTasks(new TaskFilter.Builder()
                .dueBefore(LocalDateTime.now().plusDays(2)).build());
        dueSoon.forEach(Main::print);

        // ── Filter: assigned to Bob ───────────────────────────────────────
        System.out.println("\n=== Assigned to Bob ===");
        List<Task> bobTasks = tm.filterTasks(new TaskFilter.Builder()
                .assignedUserId(bob.getId()).build());
        bobTasks.forEach(Main::print);

        // ── Search ────────────────────────────────────────────────────────
        System.out.println("\n=== Search: 'login' ===");
        tm.searchTasks("login").forEach(Main::print);

        // ── Wait for reminder to fire ─────────────────────────────────────
        Thread.sleep(3_000);

        // ── Mark t3 complete ─────────────────────────────────────────────
        tm.markComplete(bob.getId(), t3.getId());
        System.out.println("\n=== t3 after markComplete ===");
        print(t3);

        // ── History ───────────────────────────────────────────────────────
        System.out.println("\n=== History for t3 ===");
        tm.getTaskHistory(t3.getId()).forEach(System.out::println);

        // ── Delete t2 ─────────────────────────────────────────────────────
        tm.deleteTask(t2.getId());
        System.out.printf("%n=== After deleting t2: %d tasks remain ===%n",
                tm.getAllTasks().size());

        reminderService.stop();
    }

    private static void print(Task t) {
        System.out.printf("  [%s] %-35s | %-6s | %-11s | due=%-20s | assignedTo=%s%n",
                t.getId().substring(0, 8),
                t.getTitle(),
                t.getPriority(),
                t.getStatus(),
                t.getDueDate(),
                t.getAssignedUserId() != null ? t.getAssignedUserId().substring(0, 8) : "none");
    }
}
