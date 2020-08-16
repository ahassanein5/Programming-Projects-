package com.hassanein;

import java.util.Random;

public class BankAccount {

    private int balance;
    private int previousTrans;
    private String customerName;
    private int customerID;

    public BankAccount(String customerName) {
        this.customerName = customerName;
        Random ran = new Random();
        this.customerID = ran.nextInt(1000);
        this.balance = 0;
        System.out.println("Welcome " + customerName + "\nYour current balance is: $" + balance);
    }

    public void addFunds(int amount) {
        this.balance += amount;
        System.out.println("Funds added.");
        this.previousTrans = amount;
    }

    public void withdraw(int amount) {
        if((balance - amount) <= 0) {
            System.out.println("You do not have the funds to withdraw this amount");
        } else {
            this.balance -= amount;
            System.out.println("Withdraw successful, remaining balance: $" + balance);
        }
        this.previousTrans = (-1 * amount);
    }

    public void getPreviousTrans() {
        if (previousTrans < 0) {
            System.out.println("Withdrawl of " + previousTrans);
        } else {
            System.out.println("Deposit of " + previousTrans);
        }
    }

    public int getBalance() {
        return balance;
    }
}
