import java.util.Scanner;

public class main {
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        Account newAcc = new Account();
        Account Dima =  new Account("Dimitry Semenovich Anatolyevich", 547087001, 1.5,1000, Account.MoneyCurrency.EUR);
        Account Vasya =  new Account("Vasily Petrovich Yuryevich", 547087010, 3.0,505, Account.MoneyCurrency.BYN);
        Account Serge =  new Account("Serge Karatkevich Alexandrovich", 549987123, 3.1,350, Account.MoneyCurrency.BYN);
        Account Ksenya =  new Account("Ksenya Romanovskaya Vitalyevna", 547077301, 1.5,990, Account.MoneyCurrency.USD);


        System.out.print("Enter your name: ");
        newAcc.setName(in.nextLine());
        System.out.print("Enter your account number (9 numbers): ");
        newAcc.setAccNumber(in.nextLong());
        System.out.print("Enter your annual percent: ");
        newAcc.set_Percent(in.nextDouble());
        System.out.print("Enter your cash balance: ");
        newAcc.set_Amount(in.nextDouble());
        System.out.print("Enter the number of currency (1-BYN, 2-EUR, 3-USD, 4-RUB): ");
        int currNum = in.nextInt();

        Account.MoneyCurrency curr = null;
        if(currNum == 1)
            curr = Account.MoneyCurrency.BYN;
        else if(currNum == 4)
            curr = Account.MoneyCurrency.RUB;
        else if(currNum == 3)
            curr = Account.MoneyCurrency.USD;
        else if(currNum == 2)
            curr = Account.MoneyCurrency.EUR;
        else
            System.out.println("This currency doesn't exist!");

        newAcc.set_Currency(curr);

        System.out.println("******************************");

        System.out.println(newAcc.toString());

        System.out.println("******************************");

        System.out.println("Enter the balance replenishment amount: ");
        newAcc.EnlistMoney(in.nextDouble());
        System.out.println("Your balance: " + newAcc.getAmount());
        System.out.println("Enter the amount you want to withdraw: ");
        newAcc.WriteOffMoney(in.nextDouble());
        System.out.println("Your balance: " + newAcc.getAmount());
        System.out.println("Enter the period for which you want to calculate percent (in years):");
        newAcc.EnlistPercent(in.nextDouble());
        System.out.println("Your balance: " + newAcc.getAmount());


        System.out.println("******************************");

        int compResAmount = newAcc.compareTo(Dima);
        if(compResAmount == 0)
            System.out.println("Your balance is equal to Dima's balance");
        if(compResAmount == -1)
            System.out.println("Your balance is smaller than Dima's balance");
        if(compResAmount == 1)
            System.out.println("Your balance is bigger than Dima's balance");


        System.out.println("\n******************************");

        AccountsDB BD = new AccountsDB();
        BD.Add(Dima);
        BD.Add(Vasya);
        BD.Add(Serge);
        BD.Add(Ksenya);
        BD.Add(newAcc);

        for (int i = 0; i < BD.Size(); ++i)
        {
            Account acc = BD.Get(i);
            System.out.println(acc.toString());
        }

        System.out.println("******************************");
        System.out.println("After sort by name: ");
        BD.SortByName();

        for (int i = 0; i < BD.Size(); ++i)
        {
            Account acc = BD.Get(i);
            System.out.println(acc.toString());
        }

        System.out.println("******************************");
        System.out.println("After sort by account number: ");
        BD.SortByAccNum();

        for (int i = 0; i < BD.Size(); ++i)
        {
            Account acc = BD.Get(i);
            System.out.println(acc.toString());
        }

        System.out.println("******************************");
        System.out.println("After sort by amount of account: ");
        BD.SortByAmount();

        for (int i = 0; i < BD.Size(); ++i)
        {
            Account acc = BD.Get(i);
            System.out.println(acc.toString());
        }

        System.out.println("******************************");
    }
}
