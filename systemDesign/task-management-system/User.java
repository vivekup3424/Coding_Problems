import java.util.HashMap;
import java.util.Map;
import javax.naming.NameNotFoundException;

public class User {
    private String name;
    private String id;
    private Map<String, Task> tasks;
    public User(String name, String id){
        this.name = name;
        this.id = id;
        tasks = new HashMap<>();
    }
    String sanitizeDescription(String descriptionString){
        String answer = descriptionString.trim();
        return answer;
    }
    public void markTask(String description, TaskStatus newStatus) throws NameNotFoundException{
        description = sanitizeDescription(description);
        if (!tasks.containsKey(description)) {
           throw new NameNotFoundException("task with given description not found");
        }
        Task requiredTask = tasks.get(description);
        requiredTask.changeStatus(newStatus);
        return;
    }

    public void printUser(){
        System.out.println("Give user: ");
        System.out.println("\tName = "+name);
        System.out.println("\tId = "+id);
    }
}