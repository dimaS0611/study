package lab3;

public class Date {
    int m_day;
    int m_month;
    int m_year;

    public  Date()
    {}

    public Date(int day, int month, int year)
    {
        if(day < 0 || day > 30)
           System.exit(1);

        if(month < 0 || month > 12)
            System.exit(2);

        if(month == 0)
            month = 12;
        
        if(year < 0)
            System.exit(3);

        this.m_day = day;
        this.m_month = month;
        this.m_year = year;
    }

    public Date add(Date date)
    {
        int res1 = 0, res2 = 0;
        int day, month, year;

        res1 += this.m_day;
        res1 += this.m_month * 30;
        res1 += this.m_year * 365;

        res2 += date.m_day;
        res2 += date.m_month * 30;
        res2 += date.m_year * 365;

        int res3 = res1 + res2;

        year = res3 / 365;
        month = (res3 % 365) / 31;
        day =  month % 31;

        Date newDate = new Date(day, month , year);

        return newDate;
    }

    public Date subtract(Date date)
    {
        int res1 = 0, res2 = 0;
        int day, month, year;

        res1 += this.m_day;
        res1 += this.m_month * 30;
        res1 += this.m_year * 365;

        res2 += date.m_day;
        res2 += date.m_month * 30;
        res2 += date.m_year * 365;

        int res3 = 0;

        if(this.CompareUp(date))
            res3 = res1 - res2;


        if(this.CompareDown(date))
            res3 = res2 - res1;

        year = res3 / 365;
        month = (res3 % 365) / 31;
        day =  (res3 % 365) % 31;

        Date newDate = new Date(Math.abs(day), Math.abs(month), Math.abs(year));

        return newDate;
    }

    public boolean CompareUp(Date date)
    {
        if(this.m_year > date.m_year)
            return true;
        if(this.m_year == date.m_year && this.m_month > date.m_month)
            return  true;
        if(this.m_year == date.m_year && this.m_month == date.m_month && this.m_day > date.m_day)
            return  true;

        return false;
    }

    public boolean CompareDown(Date date)
    {
        if(this.m_year < date.m_year)
            return true;
        if(this.m_year == date.m_year && this.m_month < date.m_month)
            return  true;
        if(this.m_year == date.m_year && this.m_month == date.m_month && this.m_day < date.m_day)
            return  true;

        return false;
    }

    public boolean Equal(Date date)
    {
        if(this.m_year == date.m_year && this.m_month == date.m_month && this.m_day == date.m_day)
            return true;

        return false;
    }

    public void print()
    {
        System.out.print(this.m_day + "." + this.m_month + "." + this.m_year);
    }




}
