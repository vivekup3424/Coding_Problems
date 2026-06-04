import java.util.ArrayList;
import java.util.List;

class Association {

    
}

class Group{
    private String name;
    private List<User> users;
    Group(String name){
        this.name = name;
        users = new ArrayList<>();
    }
    public void addUser(User user){
        if(users.contains(user)) return;
        users.add(user);
    }
    public String getName(){
        return name;
    }
    public List<User> getUsers(){
        return users;
    }
}

class User{
    private String name;
    private List<Group> groups;
    User(String name){
        this.name = name;
        groups = new ArrayList<>();
    }
    public void joinGroup(Group group){
        if(groups.contains(group)) return;
        groups.add(group);
        group.addUser(this);
    }
    public String getName(){
        return name;
    }
}