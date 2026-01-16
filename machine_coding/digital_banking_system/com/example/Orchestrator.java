package com.example;
import java.util.HashMap;

public class Orchestrator {
    private HashMap<String, User> users;
    private Ledger ledger;
    public Orchestrator(){
        this.users = new HashMap<>();
    }
    public static void main(String[] args) {
        Orchestrator newOrchestrator = new Orchestrator();
        newOrchestrator.addUser("adf234", 100.50);
        newOrchestrator.addUser("cfv675", 8989.60);
        newOrchestrator.addUser("nhj339", 8545.00);
        newOrchestrator.printAllUsers();
    }
    public void printAllUsers(){
        for (var user : users.values()) {
            System.out.println(user.getBalance());
        }
    }
    public void transferMoney(String PayerId, String PayeeId, Double amount){
        if(this.users.containsKey(PayerId))
    }
    public void addUser(String id, Double balance){
        User newUser = new User(id, balance);
        this.users.putIfAbsent(id, newUser);
    }
}
