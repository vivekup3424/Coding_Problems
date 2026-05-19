package com.restaurant.app;

import java.util.UUID;

public class Order {
    private Integer orderId;
    private Integer customerId;
    private String[] items;
    private Integer totalAmount;
    private String status;
    Order(){
        this.orderId = UUID.randomUUID();
    }
}