package com.hassanein;

import java.util.LinkedList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
	// write your code here

        Scanner scanner = new Scanner(System.in);
        LinkedList<BankAccount> bigBank = new LinkedList<>();

        System.out.println("Please Select from the following menu options");
        System.out.println("1. New Customer \n" +
                            "2. Add Funds \n" +
                            "3. Withdraw \n" +
                            "4. Check Balance \n" +
                            "5. Check Previous Transaction \n" +
                            "6. Quit");
        int choice = scanner.nextInt();
        int i = 0;
        while(choice != 6) {
            switch (choice) {
                case 1:
                    System.out.println("Please enter your name");
                    String name = scanner.next();
                    BankAccount bank = new BankAccount(name);
                    bigBank.add(bank);
                    i++;
                    break;
                case 2:
                    if(bigBank.isEmpty()) {
                        System.out.println("No bank account is available, please create a new account");
                        break;
                    } else {
                        System.out.println("Enter the deposit amount");
                        int amount = scanner.nextInt();
                        bigBank.get(i-1).addFunds(amount);
                    }
                    break;
                case 3:
                    if(bigBank.isEmpty()) {
                        System.out.println("No bank account is available, please create a new account");
                        break;
                    } else {
                        System.out.println("Please enter the amount youd like to withdraw: ");
                        int amount = scanner.nextInt();
                        bigBank.get(i-1).withdraw(amount);
                    }
                    break;
                case 4:
                    System.out.println("Your balance is $" + bigBank.get(i-1).getBalance());
                    break;
                case 5:
                    bigBank.get(i-1).getPreviousTrans();
                    break;
                case 6:
                    System.out.println("Goodbye!");

            }
            System.out.println("Please Select from the following menu options");
            System.out.println("1. New Customer \n" +
                    "2. Add Funds \n" +
                    "3. Withdraw \n" +
                    "4. Check Balance \n" +
                    "5. Check Previous Transaction \n" +
                    "6. Quit");
            choice = scanner.nextInt();
        }



    }
}
