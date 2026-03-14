enum TaskStatus{
    TODO,
    IN_PROGRESS,
    DONE,
    CANCELLED
}
enum TaskPriority{
    LOW,
    MEDIUM,
    HIGH
}
public class Task {
    private String title;
    private String description;
    private TaskPriority taskPriority;
    private Long dueDate;
    private TaskStatus taskStatus;
    Task(String title, String description, TaskPriority taskPriority, Long dueDate ){
        this.title = title;
        this.description = description;
        this.taskPriority = taskPriority;
        this.dueDate = dueDate;
    }

    public void changeStatus(TaskStatus newStatus){
        taskStatus = newStatus;
    }

    /**
     * Show task info
     */
    public void printTask(){
        System.out.println("Given task:-");
        System.out.println("\tTitle = "+this.title);
        System.out.println("\tDescription ="+this.description);
        System.out.println("\tPriority ="+this.taskPriority);
        System.out.println("\tDue Date = "+this.dueDate);
        System.out.println("\tStatus ="+this.taskStatus);
    }

}
