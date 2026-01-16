package com.example;

import java.util.ArrayList;

public class Ledger {
    private ArrayList<String> transactions;
    public void processTransaction(String transaction){
        this.transactions.add(transaction);
    }
    public void showAllTransactions(){
        for (String trasaction : transactions) {
            System.out.println(trasaction);
        }
    }
}
