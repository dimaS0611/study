import java.util.ArrayList;
import java.util.Comparator;

public class AccountsDB{
    private ArrayList<Account> _BD = new ArrayList<Account>();

    public void Add(Account acc)
    {
        _BD.add(acc);
    }

    public void Remove(Account acc)
    {
        _BD.remove(acc);
    }

    public int Size()
    {
        return _BD.size();
    }

    public Account Get(int index)
    {
        return _BD.get(index);
    }


    public void SortByName()
    {
        Comparator<Account> accountNameComparator = Comparator.comparing(Account::getName);
        _BD.sort(accountNameComparator);
    }

    public void  SortByAccNum()
    {
        Comparator<Account> accountNumComparator = Comparator.comparing(Account::getAccNumber);
        _BD.sort(accountNumComparator);
    }

    public void  SortByAmount()
    {
        Comparator<Account> amountComparator = Comparator.comparing(Account::getAmount);
        _BD.sort(amountComparator);
    }
}
