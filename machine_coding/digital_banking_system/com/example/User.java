package com.example;

public class User{
    private String id;
    private Double balance;

    public User(String id, Double balance){
        this.id = id;
        this.balance = balance;
    }

    public String getId(){
        return this.id;
    }
    
    public Double getBalance(){
        return this.balance;
    }

    public void setId(String id) {
        this.id = id;
    }

    public void setBalance(Double balance){
        this.balance = balance;
    }
}