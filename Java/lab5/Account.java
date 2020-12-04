import java.util.Comparator;
import java.util.Iterator;

public class Account
        implements
            Comparable<Account>,
            Iterator<Account>
{
    private String _NameOfClient = "No name";
    private long _AccountNumber = 0;
    private double _Percent = 0.0;
    private double _Amount = 0.0;
    private MoneyCurrency _Currency = null;
    private int _Iterator = 0;
    private int _Counter = 0;

    public enum MoneyCurrency { BYN, USD, EUR, RUB};

    public Account(String Name, long AccountNum, double Percent, double Amount, MoneyCurrency currency)
    {
        this._NameOfClient = Name;
        this._AccountNumber = AccountNum;
        this._Percent = Percent;
        this._Amount = Amount;
        this._Currency = currency;
    }

    public Account()
    {}

    public long  getAccNumber() { return this._AccountNumber; }
    public void setAccNumber(long num) { this._AccountNumber = num; }
    public double  getPercent() { return this._Percent; }
    public void set_Percent(double num) { this._Percent = num; }
    public double  getAmount() { return this._Amount; }
    public void set_Amount(double num) { this._Amount = num; }
    public String getName() { return this._NameOfClient; }
    public void setName(String name) { this._NameOfClient = name; }
    public MoneyCurrency getCurrency() { return this._Currency; }
    public void set_Currency(MoneyCurrency currency) { this._Currency = currency; }


    public void WriteOffMoney(double Money)
    {
        this._Amount -= Money;
    }

    public void EnlistMoney(double Money)
    {
        this._Amount += Money;
    }

    public  void EnlistPercent(double TimePeriodInYears)
    {
        this._Amount += ((this._Percent / 100) * TimePeriodInYears) * this._Amount;
    }

    @Override
    public String toString()
    {
        String res = "";
        res+= getName() + " | " + getAccNumber() + " has " + getAmount() + " " + getCurrency() + "\n";
        return res;
    }

    @Override
    public int compareTo(Account obj) {
        return (Double.compare(this._Amount, obj._Amount));
    }

    public int compareByName(Account obj) {
        return (Integer.compare(this._NameOfClient.length(), obj._NameOfClient.length()));
    }

    public int compareByPercent(Account obj) {
        return ((this._Percent < obj._Percent) ? -1 : (this._Percent > obj._Percent) ? 1 : 0);
    }

    public int compareByAccNum(Account obj) {
        return ((this._AccountNumber < obj._AccountNumber) ? -1 : (this._AccountNumber > obj._AccountNumber) ? 1 : 0);
    }

    private void fieldsIter() {
        if (this._NameOfClient != "No name") {
            _Iterator = 1;
            _Counter++;
        }
        if (this._Amount != 0.0) {
            _Iterator = 2;
            _Counter++;
        }
        if (this._Percent != 0.0) {
            _Iterator = 3;
            _Counter++;
        }
        if (this._AccountNumber != 0) {
            _Iterator = 4;
            _Counter++;
        }
        if (this._Currency != null) {
            _Iterator = 5;
            _Counter++;
        }
    }

    private int value = 0;
    @Override
    public boolean hasNext() {
        fieldsIter();
        value = _Counter;

        if(value > 0) {
            value--;
            return true;
        }
        return false;
    }

    @Override
    public Account next() {
        return null;
    }
}
